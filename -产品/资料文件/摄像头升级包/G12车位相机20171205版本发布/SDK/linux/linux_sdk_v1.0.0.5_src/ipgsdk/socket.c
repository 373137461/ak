#include "socket.h"

#ifndef _WIN32
#include <errno.h>
#include <fcntl.h>
#endif

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

#ifdef _WIN32
#define MSG_NOSIGNAL 0
#define EWOULDBLOCK WSAEWOULDBLOCK
#define SOCKET_ERRNO WSAGetLastError()
#else
#define SOCKET_ERRNO errno
#endif

int socket_listen(int type, uint16_t *port, int backlog)
{
    int sockfd, ra = 1;
    struct sockaddr_in addr;
    
    sockfd = (int)socket(AF_INET, type, 0);
    if (-1 == sockfd)
        return -1;
    
    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&ra, sizeof(int)))
    {
        close(sockfd);
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(*port);
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

    if (-1 == bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
    {
        close(sockfd);
        return -1;
    }
    
    if (0 == *port)
    {
		socklen_t len = sizeof(struct sockaddr);

        if (-1 == getsockname(sockfd, (struct sockaddr*)&addr, &len))
        {
            close(sockfd);
            return -1;
        }
        
        *port = ntohs(addr.sin_port);
    }

    if (SOCK_STREAM == type)
    {
        if (-1 == listen(sockfd, backlog))
        {
            close(sockfd);
            return -1;
        }
    }
    
    return sockfd;
}

int socket_accept(int sockfd, uint32_t *local, uint32_t *remote, int timeout_ms)
{
    int ret, acceptfd;

    fd_set fds;
    struct timeval tv;
    struct sockaddr_in addr;
	socklen_t size = sizeof(struct sockaddr_in);

#ifdef _WIN32
	u_long arg = 1;
#endif

    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    
    ret = select(sockfd + 1, &fds, NULL, NULL, &tv);
    if ((ret <= 0) || !FD_ISSET(sockfd, &fds))
        return -1;
    
    acceptfd = (int)accept(sockfd, (struct sockaddr*)&addr, &size);
	if (-1 == acceptfd)
		return -1;
	
#ifdef _WIN32
    ioctlsocket(acceptfd, FIONBIO, &arg);
#endif
	
	if (NULL != remote)
		*remote = addr.sin_addr.s_addr;

	if (NULL != local)
	{
		if (-1 == getsockname(acceptfd, (struct sockaddr*)&addr, &size))
		{
			close(acceptfd);
			return -1;
		}

		*local = addr.sin_addr.s_addr;
	}

    return acceptfd;
}

int socket_recv(int sockfd, void *buf, int len, int timeout_ms)
{
    int recvd = 0, ret;
	
    while (recvd < len)
    {
        ret = recv(sockfd, (char*)buf + recvd, len - recvd, MSG_DONTWAIT);
        if (ret > 0)
        {
            recvd += ret;
        }
        else if (0 == ret)
        {
            return -2;
        }
        else
        {
            fd_set fds;
            struct timeval tv;
            
			if (EWOULDBLOCK != SOCKET_ERRNO)
                return -1;

            FD_ZERO(&fds);
            FD_SET(sockfd, &fds);
            
            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = (timeout_ms % 1000) * 1000;
            
            ret = select(sockfd + 1, &fds, NULL, NULL, &tv);
            if ((ret <= 0) || !FD_ISSET(sockfd, &fds))
				break;
        }
    }
    
    return recvd;
}

int socket_recv_unknown(int sockfd, void *buf, int len, int timeout_ms)
{
	int ret;
	fd_set fds;
    struct timeval tv;
    
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    
    ret = select(sockfd + 1, &fds, NULL, NULL, &tv);
    if ((ret <= 0) || !FD_ISSET(sockfd, &fds))
		return 0;

	ret = recv(sockfd, (char*)buf, len, MSG_DONTWAIT);
	if (0 == ret)
		return -2;

	return ret;
}

int socket_connect(const char *ip, uint16_t port, int timeout_ms)
{
    return socket_connect2(inet_addr(ip), port, timeout_ms);
}

int socket_connect2(uint32_t ip, uint16_t port, int timeout_ms)
{
    int sockfd;
    struct sockaddr_in addr;

#ifdef _WIN32
	u_long arg = 1;
#else
	int flags;
#endif

    sockfd = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
        return -1;

#ifdef _WIN32
	ioctlsocket(sockfd, FIONBIO, &arg);
#else
    flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
#endif
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip;
    addr.sin_port = htons(port);
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
    
    if (-1 == connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
    {
        fd_set fds;
        struct timeval tv;
        int ret, optval = 0;
		socklen_t optlen = sizeof(socklen_t);

        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);
        
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;

        ret = select(sockfd + 1, NULL, &fds, NULL, &tv);
        if ((ret <= 0) || !FD_ISSET(sockfd, &fds))
        {
            close(sockfd);
            return -1;
        }
        
        ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen);
        if ((0 != ret) || (0 != optval))
        {
            close(sockfd);
            return -1;
        }
    }

#ifndef _WIN32
    fcntl(sockfd, F_SETFL, flags);
#endif

    return sockfd;
}

int socket_send(int sockfd, const void *buf, int len, int timeout_ms)
{
    int sent = 0, ret;

    while (sent < len)
    {
        ret = send(sockfd, (const char*)buf + sent, 
			len - sent, MSG_NOSIGNAL | MSG_DONTWAIT);
		
        if (ret > 0)
        {
            sent += ret;
        }
        else
        {
            fd_set fds;
            struct timeval tv;
            
			if (EWOULDBLOCK != SOCKET_ERRNO)
                return -1;
            
            FD_ZERO(&fds);
            FD_SET(sockfd, &fds);

            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = (timeout_ms % 1000) * 1000;
            
            ret = select(sockfd + 1, NULL, &fds, NULL, &tv);
            if ((ret <= 0) || !FD_ISSET(sockfd, &fds))
                break;
        }
    }
    
    return sent;
}
