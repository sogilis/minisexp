#ifndef IO_H
#define IO_H

#include <iostream>

#include "miniexp.h"

namespace sx {

class io
{
public:
    io();

    miniexp_io_t *get_io();

    virtual int fputs (const char*) = 0;
    virtual int fgetc ()            = 0;
    virtual int ungetc(int)         = 0;

protected:
    miniexp_io_t _io;

private:
    static int fputs_internal (miniexp_io_t *io, const char *s);
    static int fgetc_internal (miniexp_io_t *io);
    static int ungetc_internal(miniexp_io_t *io, int i);
};


class streamio : public io
{
public:
    streamio(std::iostream *stream);

    virtual int fputs(const char *s);
    virtual int fgetc();
    virtual int ungetc(int i);

private:
    std::iostream *stream;
};

}

#endif // IO_H
