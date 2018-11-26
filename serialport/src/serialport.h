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

enum sp_return {
    SP_OK = 0,
    SP_ERROR_FAIL = -1,
};

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

/**
 * Init termios default config
 *
 * @param term struct termios pointer
 * @return 0 Success -1 Failure
 */
enum sp_return iot_sp_termios_init(struct termios *term);

/**
 * Init serialport config
 *
 * @param port struct sp_port pointer
 * @param path serialport path
 * @return 0 Success -1 Failure
 */
enum sp_return iot_sp_init(struct sp_port *sp_port, char *path);

/**
 * open serialport path
 *
 * @param port struct sp_port pointer
 * @return 0 Success -1 Failure
 */
enum sp_return iot_sp_open(struct sp_port *port);

/**
 * read for serialport
 *
 * @param port struct sp_port pointer
 * @param buff read buff
 * @param len  buff len
 * @return read for serialport len
 */
int iot_sp_read(struct sp_port *port, unsigned char *buff, size_t len);

/**
 * write to serialport
 *
 * @param port struct sp_port pointer
 * @param buff write buff
 * @param len  write len
 * @return write to serialport len
 */
int iot_sp_write(struct sp_port *port, unsigned char *buff, size_t len);

/**
 * close serialport
 *
 * @param port struct sp_port pointer
 * @return write to serialport len
 */
enum sp_return iot_sp_close(struct sp_port *port);

#ifdef __cplusplus
}
#endif


#endif //LIB_IOT_CLIENT_SERIALPORT_H
