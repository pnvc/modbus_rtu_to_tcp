#include "tty_settings.h"

void set_tty_as_uart(int32_t fd, speed_t baud)
{
	struct termios old_p;
	struct termios new_p;
	if (tcgetattr(fd, &old_p) < 0) {
		fprintf(stderr, "Termios: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	memcpy(&new_p, &old_p, sizeof(old_p));
	new_p.c_lflag &= ~(ISIG | ICANON | XCASE | ECHO | ECHOE | ECHOK
			| ECHONL | ECHOCTL | ECHOPRT | ECHOKE 
			| FLUSHO | NOFLSH | TOSTOP | PENDIN | IEXTEN);
	new_p.c_cc[VMIN] = 1;
	new_p.c_cc[VTIME] = 0;
	cfsetspeed(&new_p, baud);
	if (tcsetattr(fd, TCSANOW, &new_p) < 0) {
		fprintf(stderr, "Termios: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
