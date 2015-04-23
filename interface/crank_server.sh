#!/bin/sh

echo "Starting server, listening on CAN0..."
candump can0 | ./server.py