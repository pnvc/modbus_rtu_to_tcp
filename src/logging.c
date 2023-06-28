#include "logging.h"

void start_logging()
{
	openlog("modbus-uart-tcp", LOG_PID, 0);
	log_info_msg("ModBus UART <-> ModBus TCP daemon started");
}

void log_info_msg(const char * msg) { syslog(LOG_INFO, msg, 0); }

void log_crit_msg(const char * msg) { syslog(LOG_CRIT, msg, 0); }
