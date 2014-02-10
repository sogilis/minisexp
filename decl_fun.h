#ifndef SX_DECL_DECL_FUN_H
#define SX_DECL_DECL_FUN_H

#include <llvm/IR/Module.h>

#include "sexpr.h"

namespace sx {
namespace decl {

class fun : public sx::sexpr
{
    std::string name;
public:
    fun(std::string name, sexpr expr);

    sexpr instr_list();

    void generate(llvm::Module *module);
};

} // namespace decl
} // namespace sx

#endif // SX_DECL_DECL_FUN_H
