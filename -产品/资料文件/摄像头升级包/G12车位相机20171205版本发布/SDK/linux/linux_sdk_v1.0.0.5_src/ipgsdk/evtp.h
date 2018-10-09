#ifndef _EVTP__H_
#define _EVTP__H_

#include <stdint.h>
#include "Log.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* evtp_handle_t;
typedef void (*evtp_callback_t)(void *param, 
	uint32_t type, void *data, int len);

evtp_handle_t evtp_start(const char *ip, uint16_t port, 
	evtp_callback_t callback, void *param);

evtp_handle_t evtp_start_passwd(const char *ip, uint16_t port, 
	const char *passwd, evtp_callback_t callback, void *param);

evtp_handle_t evtp_start_withLog(const char *ip, uint16_t port, 
	CLog *log, evtp_callback_t callback, void *param);

evtp_handle_t evtp_start_passwd_withLog(const char *ip, uint16_t port, 
	CLog *log, const char *passwd, evtp_callback_t callback, void *param);

void evtp_stop(evtp_handle_t handle);
int evtp_get_status(evtp_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif