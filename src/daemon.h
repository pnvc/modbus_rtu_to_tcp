#ifndef DAEMON_H_SENTRY
#define DAEMON_H_SENTRY

#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "error.h"
#include "logging.h"
#include "init_daemon.h"
#include "sys_calls.h"
#include "crc.h"
#include "protocol_convert.h"

#define BUF_SIZE 1024

static const unsigned char CRC_ERROR[] = "Non valid CRC\n";
static const unsigned char LEN_ERROR[] = "Big request length\n";
static const char UART_TTY[] = "/dev/ttyS0";
static const char MODBUS_IP[] = "192.168.1.127";
static uint16_t MODBUS_PORT = 502;
static unsigned char buf[BUF_SIZE];

#endif
