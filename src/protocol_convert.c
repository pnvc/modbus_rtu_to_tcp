#include "protocol_convert.h"

void uart_to_tcp(unsigned char * buf, ssize_t * len)
{

	ssize_t new_len = *len + 4;
	unsigned char *b = (unsigned char*)calloc(new_len, sizeof(unsigned char));
	b[5] = *len - 2;
	memcpy(b+6, buf, b[5]);
	memcpy(buf, b, new_len);
	*len = new_len;
	free(b);
}

void tcp_to_uart(unsigned char * buf, ssize_t * len)
{
	ssize_t new_len = *len - 4;
	unsigned char *b = (unsigned char*)calloc(new_len, sizeof(unsigned char));
	memcpy(b, buf+6, new_len - 2);
	uint16_t crc16 = modbus_crc16((const unsigned char*)b, new_len - 2);
	b[new_len - 1] = crc16 & 0xff;
	crc16 >>= 8;
	b[new_len - 2] = crc16 & 0xff;
	memcpy(buf, b, new_len);
	*len = new_len;
	while (buf[new_len])
		buf[new_len++] = 0;
}
