/*
 * Copyright (c) Zhang WenChao <zhangwenchao001@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIB_IOT_CLIENT_SERIALPORT_H
#define LIB_IOT_CLIENT_SERIALPORT_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <termios.h>
#include <stdlib.h>

enum sp_return
{
    SP_OK = 0,
    SP_ERROR_FAIL = -1,
};

struct sp_port
{
    char path[50];
    int fd;
    int mode;
    struct termios term;
    unsigned long nspeed;
    int ncsize;
    int nparity;
    int nstop;
};

enum sp_mode
{
    SP_MODE_READ = 0x0000,
    SP_MODE_WRITE = 0x0001,
    SP_MODE_READ_WRITE = 0x0002
};

enum sp_port_parity
{
    PARITY_NULL = 0,
    PARITY_EVEN = 1,
    PARITY_ODD = 2,
    PARITY_SPACE = 0
};

enum sp_port_stop
{
    STOP_A = 1,
    STOP_B = 2
};

/**
 * Init serialport config
 *
 * @param  port struct sp_port pointer
 * @param  path serialport path
 * @return sp_return
 */
enum sp_return iot_sp_init(struct sp_port *sp_port, char *path);

/**
 * Init termios default config
 *
 * @param  term struct termios pointer
 * @return sp_return
 */
enum sp_return iot_sp_termios_init(struct sp_port *sp_port);

/**
 * open serialport path
 *
 * @param  port struct sp_port pointer
 * @return sp_return
 */
enum sp_return iot_sp_open(struct sp_port *port);

/**
 * read for serialport
 *
 * @param  port struct sp_port pointer
 * @param  buff read buff
 * @param  len  buff len
 * @return read for serialport len
 */
int iot_sp_read(struct sp_port *port, unsigned char *buff, size_t len);

/**
 * write to serialport
 *
 * @param  port struct sp_port pointer
 * @param  buff write buff
 * @param  len  write len
 * @return write to serialport len
 */
int iot_sp_write(struct sp_port *port, unsigned char *buff, size_t len);

/**
 * close serialport
 *
 * @param  port struct sp_port pointer
 * @return sp_return write to serialport len
 */
enum sp_return iot_sp_close(struct sp_port *port);

/**
 * change open serialport mode
 *
 * @param  port struct sp_port pointer
 * @param  mode sp_mode
 * @return sp_return
 */
enum sp_return iot_sp_change_mode(struct sp_port *port, enum sp_mode mode);

/**
 * change serialport baud rate
 *
 * @param  port struct sp_port pointer
 * @param  speed standard speeds
 * @return sp_return
 */
enum sp_return iot_sp_change_baud_rate(struct sp_port *port, unsigned long speed);

/**
 * change serialport character size
 *
 * @param  port struct sp_port pointer
 * @param  size character size
 * @return sp_return
 */
enum sp_return iot_sp_change_character_size(struct sp_port *port, int size);

/**
 * change serialport parity checking
 *
 * @param  port   struct sp_port pointer
 * @param  parity struct sp_port_parity
 * @return sp_return
 */
enum sp_return iot_sp_change_parity(struct sp_port *port, enum sp_port_parity parity);

/**
 * change serialport stop bits
 *
 * @param  port   struct sp_port pointer
 * @param  parity struct sp_port_stop
 * @return sp_return
 */
enum sp_return iot_sp_change_stop(struct sp_port *port, enum sp_port_stop stop);

#ifdef __cplusplus
}
#endif


#endif //LIB_IOT_CLIENT_SERIALPORT_H
