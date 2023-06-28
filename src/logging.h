#ifndef LOGGING_G_SENTRY
#define LOGGING_G_SENTRY

#include <syslog.h>

void start_logging();
void log_info_msg(const char * msg);
void log_crit_msg(const char * msg);

#endif
