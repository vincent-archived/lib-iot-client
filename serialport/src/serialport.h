/*
 * Copyright (c) Zhang WenChao <zhangwenchao001@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIB_IOT_CLIENT_SERIALPORT_H
#define LIB_IOT_CLIENT_SERIALPORT_H

#include <stdint.h>
#include <termios.h>
#include <stdlib.h>

#define	EXIT_FAILURE_EXTRA	-1

struct sp_port
{
    char           path[50];
    int            fd;
    int            mode;
    struct termios term;
};

enum sp_mode
{

    SP_MODE_READ = 0x0000,

    SP_MODE_WRITE = 0x0001,

    SP_MODE_READ_WRITE = 0x0002
};

int iot_sp_init(struct sp_port *sp_port, char *path);
int iot_sp_open(struct sp_port *port);
int iot_sp_read(struct sp_port *port, unsigned char *buff, size_t len);
int iot_sp_write(struct sp_port *port, unsigned char *buff, size_t len);

#endif //LIB_IOT_CLIENT_SERIALPORT_H
