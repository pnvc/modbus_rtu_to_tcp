#!/bin/bash

cat /var/log/syslog | grep -a modbus-uart-tcp | tail -20
