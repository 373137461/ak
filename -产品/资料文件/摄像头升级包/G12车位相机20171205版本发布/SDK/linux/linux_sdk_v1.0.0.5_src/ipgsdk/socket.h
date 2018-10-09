#ifndef _SOCKET__H_
#define _SOCKET__H_

#include <stdint.h>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#ifdef _WIN32
#define socklen_t int
#define close closesocket
#define MSG_DONTWAIT 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

int socket_listen(int type, uint16_t *port, int backlog);
int socket_accept(int sockfd, uint32_t *local, uint32_t *remote, int timeout_ms);
int socket_recv(int sockfd, void *buf, int len, int timeout_ms);
int socket_recv_unknown(int sockfd, void *buf, int len, int timeout_ms);

int socket_connect(const char *ip, uint16_t port, int timeout_ms);
int socket_connect2(uint32_t ip, uint16_t port, int timeout_ms);
int socket_send(int sockfd, const void *buf, int len, int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif