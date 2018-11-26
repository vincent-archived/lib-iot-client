/*
 * Copyright (c) Zhang WenChao <zhangwenchao001@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "serialport.h"

enum sp_return iot_sp_termios_init(struct termios *term)
{
    term->c_cflag |= (CLOCAL | CREAD);
    term->c_cflag &= ~CSIZE;
    term->c_cflag &= ~PARENB;
    cfsetispeed(term, B115200);
    cfsetospeed(term, B115200);
    term->c_cc[VTIME]  = 0;
    term->c_cc[VMIN]   = 0;
    return SP_OK;
}

enum sp_return iot_sp_init(struct sp_port *port, char *path)
{
    strcpy(port->path, path);
    port->mode = SP_MODE_READ_WRITE;
    iot_sp_termios_init(&port->term);
    return SP_OK;
}

enum sp_return iot_sp_open(struct sp_port *port)
{

    int flags = (O_NONBLOCK | O_NOCTTY | port->mode);
    port->fd = open(port->path, flags);
    if (port->fd == SP_ERROR_FAIL) {
        return SP_ERROR_FAIL;
    }
    if ((tcsetattr(port->fd, TCSANOW, &port->term)) != EXIT_SUCCESS) {
        return SP_ERROR_FAIL;
    }
    return SP_OK;
}

int iot_sp_read(struct sp_port *port, unsigned char *buff, size_t len)
{
    return (int)read(port->fd, buff, len);
}

int iot_sp_write(struct sp_port *port, unsigned char *buff, size_t len)
{
    return (int)write(port->fd, buff, len);
}

enum sp_return iot_sp_close(struct sp_port *port)
{
    return close(port->fd);
}