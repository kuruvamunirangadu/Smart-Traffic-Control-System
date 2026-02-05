#!/usr/bin/env bash
set -e
gcc src/traffic_controller.c -o traffic_controller_sim
./traffic_controller_sim
