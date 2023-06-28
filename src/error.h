#ifndef ERROR_H_SENTRY
#define ERROR_H_SENTRY

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "logging.h"

void check_crit_error(int32_t e);

#endif
