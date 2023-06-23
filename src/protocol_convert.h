#ifndef PROTOCOL_CONVERT_H_SENTRY
#define PROTOCOL_CONVERT_H_SENTRY

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "crc.h"

void uart_to_tcp(unsigned char * buf, ssize_t * len);
void tcp_to_uart(unsigned char * buf, ssize_t * len);

#endif
