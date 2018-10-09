#ifndef _SM__H_
#define _SM__H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*sm_callback_t)(const void *data, int len, void *param);
typedef void* sm_handle_t;

int sm_init();
void sm_fini();

sm_handle_t sm_connect(const char *ip, unsigned short port, sm_callback_t callback, void *param);
void sm_close(sm_handle_t handle);

int sm_send(sm_handle_t handle, const void *data, int len, int timeout_ms);
int sm_get_status(sm_handle_t handle);
void sm_close_session(sm_handle_t handle, int status);
int sm_get_sockfd(sm_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif