#include "error.h"

void check_crit_error(int32_t e)
{
	if (e < 0) {
		log_crit_msg(strerror(errno));
		exit(EXIT_FAILURE);
	}
}
