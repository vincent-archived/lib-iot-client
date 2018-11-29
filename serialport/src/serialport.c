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

enum sp_return iot_sp_init(struct sp_port *port, char *path)
{
    port->nspeed = B115200;
    port->ncsize = 8;
    port->nparity = PARITY_NULL;
    port->nstop = STOP_A;
    strcpy(port->path, path);
    port->mode = SP_MODE_READ_WRITE;
    iot_sp_termios_init(port);
    return SP_OK;
}

enum sp_return iot_sp_termios_init(struct sp_port *port)
{
    memset(&port->term, 0, sizeof(struct termios));

    port->term.c_cflag |= (CLOCAL | CREAD);
    port->term.c_cflag &= ~CSIZE;

    switch (port->ncsize) {
        case 5:
            port->term.c_cflag |= CS5;
            break;
        case 6:
            port->term.c_cflag |= CS6;
            break;
        case 7:
            port->term.c_cflag |= CS7;
            break;
        case 8:
            port->term.c_cflag |= CS8;
            break;
        default:
            break;
    }

    switch (port->nparity) {
        case PARITY_NULL:
            port->term.c_cflag &= ~PARENB;
            port->term.c_cflag &= ~CSTOPB;
            port->term.c_cflag &= ~CSIZE;
            port->term.c_cflag |= CS8;
            break;
        case PARITY_EVEN:
            port->term.c_cflag |= PARENB;
            port->term.c_cflag &= ~PARODD;
            port->term.c_cflag &= ~CSTOPB;
            port->term.c_cflag &= ~CSIZE;
            port->term.c_cflag |= CS7;
            break;
        case PARITY_ODD:
            port->term.c_cflag |= PARENB;
            port->term.c_cflag |= PARODD;
            port->term.c_cflag &= ~CSTOPB;
            port->term.c_cflag &= ~CSIZE;
            port->term.c_cflag |= CS7;
            break;
        default:
            break;
    }
    cfsetispeed(&port->term, port->nspeed);
    cfsetospeed(&port->term, port->nspeed);
    port->term.c_cc[VTIME] = 0;
    port->term.c_cc[VMIN] = 0;
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
    return (int) read(port->fd, buff, len);
}

int iot_sp_write(struct sp_port *port, unsigned char *buff, size_t len)
{
    return (int) write(port->fd, buff, len);
}

enum sp_return iot_sp_close(struct sp_port *port)
{
    return close(port->fd);
}

enum sp_return iot_sp_change_mode(struct sp_port *port, enum sp_mode mode)
{
    port->mode = mode;
    return SP_OK;
}

enum sp_return iot_sp_change_baud_rate(struct sp_port *port, unsigned long speed)
{
    cfsetispeed(&port->term, speed);
    cfsetospeed(&port->term, speed);
    return SP_OK;
}

enum sp_return iot_sp_change_character_size(struct sp_port *port, int size)
{
    port->ncsize = size;
    return SP_OK;
}

enum sp_return iot_sp_change_parity(struct sp_port *port, enum sp_port_parity parity)
{
    port->nparity = parity;
    return SP_OK;
}

enum sp_return iot_sp_change_stop(struct sp_port *port, enum sp_port_stop stop)
{
    port->nstop = stop;
    return SP_OK;
}