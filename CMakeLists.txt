cmake_minimum_required(VERSION 3.0)

project(MODBUS_RTU_ROUTE)

set (src
	src/crc.c
	src/daemon.c
	src/error.c
	src/init_daemon.c
	src/logging.c
	src/protocol_convert.c
	src/sys_calls.c
	src/tty_settings.c
	)

set (headers
	src/crc.h
	src/daemon.h
	src/error.h
	src/init_daemon.h
	src/logging.h
	src/protocol_convert.h
	src/sys_calls.h
	src/tty_settings.h
	)

add_executable(exe ${src} ${headers})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
