#include "daemon.h"

int32_t main(int32_t argc, char **argv)
{
	printf("Run 'check.sh' script to see running status from syslog\n\
Kill it with 'sudo kill -15 [PID]'\n");
	start_process_as_daemon();
	start_logging();
	int32_t new_tty = Open_tty("/dev/ttyAMA3", SPEED_BAUD);
	int32_t uart = Open_tty(UART_TTY, SPEED_BAUD);
	int32_t sock;
connection:
	sock = Inet_stream_socket();
	Connect(sock, MODBUS_IP, MODBUS_PORT);
	ssize_t rr; // rr - recv/read return
	for (;;) {
		rr = Read(uart, buf, BUF_SIZE);
		if (rr < BUF_SIZE - 4 && check_crc(buf, rr)) {
			if (buf[0] < 100) {
				uart_to_tcp(buf, &rr);
				Send(sock, buf, rr);
				explicit_bzero(buf, rr);
				rr = Recv(sock, buf, BUF_SIZE);
				if (!rr) {
					close(sock);
					sock = 0;
					log_info_msg("Remote ModBus TCP \
closed connection or stopped runtime");
					goto connection;
				}
				tcp_to_uart(buf, &rr);
				usleep(500000);
				write(uart, buf, rr);
			} else {
				/* prototype route for /dev/ttyAMA3 */
				uint16_t crc;
				switch (buf[0]) {
					case 100:
					Write(new_tty, buf + 1, rr - 2);
					explicit_bzero(buf + 1, rr - 1);
					sleep(1);
					rr = Read(new_tty, buf + 1, BUF_SIZE - 1);
					if (check_crc(buf + 1, rr)) {
						++rr;
						crc = modbus_crc16(buf, rr);
						buf[rr] = crc & 0xff;
						crc >>= 8;
						buf[rr + 1] = crc & 0xff;
						rr += 2;
						Write(uart, buf, rr);
					} else {
						Write(new_tty, CRC_ERROR,
							sizeof(CRC_ERROR) - 1);
						Write(uart, CRC_ERROR,
							sizeof(CRC_ERROR) - 1);
					}
					default: break;
				}
				/* prototype route for /dev/ttyAMA3 */
			}
			explicit_bzero(buf, rr);
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
