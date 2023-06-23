#include "crc.h"

uint16_t modbus_crc16(const unsigned char * buf, ssize_t len)
{
	uint16_t init = 0xffff;
	while (len--) {
		init ^= *buf++;
		for (size_t i = 0; i < 8; i++) {
			if (init & 1) {
				init >>= 1;
				init ^= 0xa001;
			} else
				init >>= 1;
		}
	}
	return init;
}

uint8_t check_crc(const unsigned char * buf, ssize_t len)
{
	uint16_t crc = modbus_crc16(buf, len - 2);
	uint8_t big = *(buf + len - 2);
	uint8_t lit = *(buf + len - 1);
	uint16_t crc_from_buf = big;
	crc_from_buf <<= 8;
	crc_from_buf += lit;
	if (crc_from_buf != crc)
		return 0;
	return 1;
}
