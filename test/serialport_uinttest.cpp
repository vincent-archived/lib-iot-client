/*
 * Copyright (c) Zhang WenChao <zhangwenchao001@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "serialport.h"

namespace {

    char *tty_path = const_cast<char *>("/dev/tty.usbserial-144100");

    struct sp_port port;

    TEST(SerialPort, Init) {
        iot_sp_init(&port, tty_path);
    }

    TEST(SerialPort, Open) {
        iot_sp_open(&port);
    }

    TEST(SerialPort, Read) {
        unsigned char buff[100] = {0};
        size_t len = sizeof(buff);
        int nread = iot_sp_read(&port, buff, len);
        if (nread > 0) {
            printf("Read %d %s \n", nread, buff);
        }
    }

    TEST(SerialPort, Write) {
        unsigned char buff[100] = {0};
        size_t len = sizeof(buff);
        int nwrite= iot_sp_write(&port, buff, len);
        if (nwrite > 0) {
            printf("Write %d \n", nwrite);
        }
    }
}
