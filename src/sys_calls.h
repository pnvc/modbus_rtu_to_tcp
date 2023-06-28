#ifndef SYS_CALLS_H_SENTRY
#define SYS_CALLS_H_SENTRY

#include <inttypes.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <termios.h>
#include "error.h"
#include "logging.h"
#include "tty_settings.h"

int32_t Open_tty(const char * tty, speed_t baud);
int32_t Inet_stream_socket();
void Connect(int32_t sock, const char * ip, uint16_t port);
ssize_t Read(int32_t fd, unsigned char *buf, ssize_t buf_len);
void Write(int32_t fd, const unsigned char *buf, ssize_t len);
void Send(int32_t s, const unsigned char *buf, ssize_t len);
ssize_t Recv(int32_t s, unsigned char *buf, ssize_t buf_len);

#endif
