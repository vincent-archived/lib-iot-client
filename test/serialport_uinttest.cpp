/*
 * Copyright (c) Zhang WenChao <zhangwenchao001@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "serialport.h"

namespace {

    char *tty_path = const_cast<char *>("/dev/tty.usbserial-146100");

    struct sp_port port;

    TEST(SerialPort, Init)
    {
        iot_sp_init(&port, tty_path);
    }

    TEST(SerialPort, Change)
    {
        iot_sp_change_mode(&port, SP_MODE_READ_WRITE);
        iot_sp_change_baud_rate(&port, 115200);
        iot_sp_change_parity(&port, PARITY_NULL);
        iot_sp_change_character_size(&port, 8);
        iot_sp_change_stop(&port, STOP_A);
    }

    TEST(SerialPort, Open)
    {
        iot_sp_open(&port);
    }

    TEST(SerialPort, Read)
    {
        unsigned char buff[100] = {0};
        size_t len = sizeof(buff);
        int nread = iot_sp_read(&port, buff, len);
        if (nread > 0) {
            printf("Read %d %s \n", nread, buff);
        }
    }

    TEST(SerialPort, Write)
    {
        unsigned char buff[100] = {0};
        std::strcpy((char *) &buff, "This is test case");
        size_t len = sizeof(buff);
        int nwrite = iot_sp_write(&port, buff, len);
        if (nwrite > 0) {
            printf("Write %d \n", nwrite);
        }
        sleep(2);
    }

    TEST(SerialPort, Cloce)
    {
        iot_sp_close(&port);
    }
}
