#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "serialport.h"

int iot_sp_termios_init(struct termios *term)
{
    term->c_cflag |= (CLOCAL | CREAD);
    term->c_cflag &= ~CSIZE;
    term->c_cflag &= ~PARENB;
    cfsetispeed(term, B115200);
    cfsetospeed(term, B115200);
    term->c_cc[VTIME]  = 0;
    term->c_cc[VMIN]   = 0;

    return 0;
}

int iot_sp_init(struct sp_port *port, char *path)
{
    strcpy(port->path, path);
    port->mode = SP_MODE_READ_WRITE;
    iot_sp_termios_init(&port->term);
    return EXIT_SUCCESS;
}

int iot_sp_open(struct sp_port *port)
{

    int flags = (O_NONBLOCK | O_NOCTTY | port->mode);
    port->fd = open(port->path, flags);
    if (port->fd == EXIT_FAILURE_EXTRA) {
        return EXIT_FAILURE;
    }
    if ((tcsetattr(port->fd, TCSANOW, &port->term)) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int iot_sp_read(struct sp_port *port, unsigned char *buff, size_t len)
{
    ssize_t nread;
    nread = (size_t) read(port->fd, buff, len);
    return (int)nread;
}

int iot_sp_write(struct sp_port *port, unsigned char *buff, size_t len)
{
    ssize_t nwrite;
    nwrite = (size_t) write(port->fd, buff, len);
    return (int)nwrite;
}

int iot_sp_close(char *path)
{
    return EXIT_SUCCESS;
}