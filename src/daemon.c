#include "daemon.h"
#include "logging.h"

int32_t main(int32_t argc, char **argv)
{
	printf("Run 'check.sh' script to see running status from syslog\n\
Kill it with 'sudo kill -15 [PID]'\n");
	start_process_as_daemon();
	start_logging();
	int32_t uart = Open_tty(UART_TTY);
	int32_t flags = fcntl(uart, F_GETFL);
	flags &= ~O_NONBLOCK;
	fcntl(uart, F_SETFL, flags);
	int32_t sock;
connection:
	sock = Inet_stream_socket();
	Connect(sock, MODBUS_IP, MODBUS_PORT);
	ssize_t rr; // rr - recv/read return
	for (;;) {
		rr = Read(uart, buf, BUF_SIZE);
		if (rr < BUF_SIZE - 4 && check_crc(buf, rr)) {
			uart_to_tcp(buf, &rr);
			Send(sock, buf, rr);
			explicit_bzero(buf, rr);
			rr = Recv(sock, buf, BUF_SIZE);
			if (!rr) {
				close(sock);
				sock = 0;
				log_info_msg("Remote ModBus TCP closed connection or stopped runtime");
				goto connection;
			}
			tcp_to_uart(buf, &rr);
			write(uart, buf, rr);
		} else {
			if (rr > 1019)
				Write(uart, LEN_ERROR, sizeof(LEN_ERROR) - 1);
			else
				Write(uart, CRC_ERROR, sizeof(CRC_ERROR) - 1);
		}
		usleep(500000);
	}
	return 0;
}
