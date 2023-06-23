#!/bin/bash

cat /var/log/syslog | grep modbus-uart-tcp | tail -20
