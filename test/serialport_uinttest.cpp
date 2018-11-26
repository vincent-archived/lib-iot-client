/*
 * Copyright (c) Zhang WenChao <zhangwenchao001@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"

extern "C" {
#include "serialport.h"
}

namespace {

    char *tty_1_path = const_cast<char *>("/dev/tty.usbserial-144100");

    struct sp_port port;

    TEST(SerialPort, Open) {
        iot_sp_init(&port, tty_1_path);
    }
}