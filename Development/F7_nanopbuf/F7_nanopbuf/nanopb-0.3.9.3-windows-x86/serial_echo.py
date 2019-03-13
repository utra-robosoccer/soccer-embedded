#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import time

import RobotCmd_pb2

num_round_trips = 100
baudrate = 230400
port = 'COM4'
timeout_sec = 1
string_to_echo = "Hello, this string's case will be INVERTED."

with serial.Serial(port, baudrate, timeout=timeout_sec) as ser:
    for i in range(num_round_trips):
        # Instantiate a new message of type Hello
        message = RobotCmd_pb2.Hello()

        # Write encoded bytes to the Hello.message field
        original = string_to_echo.encode()
        message.message = original

        # Serialize the message to a string before sending
        original_serialized = message.SerializeToString()
        ser.write(original_serialized)

        # Read back the echoed message, which has been encoded
        # as a string by the MCU
        message.ParseFromString(ser.read(len(string_to_echo) + 2))

        # See what both the serialized form and the returned
        # Hello.message field look like
        returned_serialized = message.SerializeToString()
        returned = message.message
        print("round trip {}:\n    original: {} serialized: {}\n    returned: {} serialized: {}".format(i, original, original_serialized, returned, returned_serialized))
