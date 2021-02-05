#ifndef _WIFI_SERVICE_H_
#define _WIFI_SERVICE_H_

#include "system_core.h"

static uint8_t wifi_state = 0;		//0:未完成初始化

void wifi_service(void);
void wifi_init(void);

#endif
