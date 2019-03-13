#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import time

import RobotCmd_pb2

with serial.Serial('COM4', 230400, timeout=1) as ser:
    for i in range(10000):
        message = RobotCmd_pb2.Hello()
        message.message = b"hello"
        orig = message.SerializeToString()
        ser.write(orig)
        data = ser.read(7)
        print("iteration {}:\n  orig: {}\n  data: {}".format(i, orig, data))
        