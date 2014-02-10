#include "io.h"

namespace sx {

io::io() :
    _io(miniexp_io)
{
    _io.data[0] = this;
    _io.fputs  = io::fputs_internal;
    _io.fgetc  = io::fgetc_internal;
    _io.ungetc = io::ungetc_internal;
}

miniexp_io_t *io::get_io()
{
    return &_io;
}

int io::fputs_internal(miniexp_io_t *miniexp_io, const char *s)
{
    io *self = static_cast<io*>(miniexp_io->data[0]);
    return self->fputs(s);
}

int io::fgetc_internal(miniexp_io_t *miniexp_io)
{
    io *self = static_cast<io*>(miniexp_io->data[0]);
    return self->fgetc();
}

int io::ungetc_internal(miniexp_io_t *miniexp_io, int i)
{
    io *self = static_cast<io*>(miniexp_io->data[0]);
    return self->ungetc(i);
}

}

sx::streamio::streamio(std::iostream *stream) : stream(stream)
{

}

int sx::streamio::fputs(const char *s)
{
    std::string str(s);
    stream->write(str.c_str(), str.length());
    return str.length();
}

int sx::streamio::fgetc()
{
    return stream->get();
}

int sx::streamio::ungetc(int c)
{
    stream->putback(c);
}
