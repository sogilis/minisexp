#ifndef SX_DECLS_DECLS_DEF_H
#define SX_DECLS_DECLS_DEF_H

#include <llvm/IR/Module.h>

#include "sexpr.h"

namespace sx {
namespace decl {

class def : public sx::sexpr
{
public:
    def(sexpr expr);

    sexpr declare_list();
    sexpr declare_name();

    void generate(llvm::Module *module);
};

} // namespace decl
} // namespace sx

#endif // SX_DECLS_DECLS_DEF_H
