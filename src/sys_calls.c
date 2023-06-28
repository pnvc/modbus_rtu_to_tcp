#include "sys_calls.h"

int32_t Open_tty(const char * tty, speed_t baud)
{
	int32_t tty_fd = open(tty, O_RDWR | O_NOCTTY | O_ASYNC);
	check_crit_error(tty_fd);
	log_info_msg("Tty is opened");
	set_tty_as_uart(tty_fd, baud);
	return tty_fd;
}

int32_t Inet_stream_socket()
{
	int s = socket(AF_INET, SOCK_STREAM, 0);
	check_crit_error(s);
	log_info_msg("Socket inited");
	return s;
}

void Connect(int32_t sock, const char * ip, uint16_t port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	int32_t ipr = inet_pton(AF_INET, ip, &addr.sin_addr);
	check_crit_error(ipr);
	if (!ipr) { log_crit_msg("Bad IP"); exit(1); }
	int32_t cr = 0;
	while (1) {
		cr = connect(sock, (const struct sockaddr*) & addr, sizeof(addr));
		if (cr < 0) {
			if (errno == ECONNREFUSED) {
				log_info_msg("Cant connect to the ModBus TCP (is runtime not running?)");
				sleep(5);
			}
			else
				check_crit_error(cr);
		} else break;
	}
	log_info_msg("Connection to the ModBus TCP is established");
}

ssize_t Read(int32_t fd, unsigned char *buf, ssize_t buf_len)
{
	ssize_t rr = read(fd, buf, buf_len);
	check_crit_error(rr);
	return rr;
}

void Write(int32_t fd, const unsigned char *buf, ssize_t len)
{
	ssize_t swr = write(fd, buf, len);
	check_crit_error(swr);
}

void Send(int32_t s, const unsigned char *buf, ssize_t len)
{
	ssize_t swr = send(s, buf, len, 0);
	check_crit_error(swr);
}

ssize_t Recv(int32_t s, unsigned char *buf, ssize_t buf_len)
{
	ssize_t rr = recv(s, buf, buf_len, 0);
	check_crit_error(rr);
	return rr;
}
