#ifndef _SC__H_
#define _SC__H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*sc_callback_t)(const char *ip, unsigned short port, const void *data, int len, void *param);
typedef void *sc_handle_t;

int sc_init();
void sc_fini();

sc_handle_t sc_connect(const char *ip, unsigned short port, sc_callback_t callback, void *param);
void sc_close(sc_handle_t handle);

int sc_send(sc_handle_t handle, const void *data, int len, int timeout_ms);
int sc_get_sockfd(sc_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif