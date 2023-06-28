#ifndef TTY_SETTINGS_H_SENTRY
#define TTY_SETTINGS_H_SENTRY

#include <termios.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void set_tty_as_uart(int32_t fd, speed_t baud);

#endif
