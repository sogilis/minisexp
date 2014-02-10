#ifndef SX_DECL_H
#define SX_DECL_H

#error "invalid decl.h"
#include "sexpr.h"

namespace sx {

class decl : public sexpr
{
public:
    decl(minivar_t expr) : sexpr(expr) {}
    bool is_fun();
};

} // namespace sx

#endif // SX_DECL_H
