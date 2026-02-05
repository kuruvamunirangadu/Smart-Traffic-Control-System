#!/usr/bin/env bash
set -e
gcc src/traffic_controller_pigpio.c -o traffic_controller -lpigpio -lrt
sudo ./traffic_controller
