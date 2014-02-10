#ifndef SX_SEXPR_H
#define SX_SEXPR_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

#include <string>
#include "miniexp.h"

namespace sx {

class sexpr
{
protected:
    minivar_t expr;
public:
    sexpr(minivar_t expr);
    sexpr(sexpr &expr);

    std::string to_string();

    bool is_nil();
    bool is_string();
    std::string to_name();
    void print();
    sexpr car();
    sexpr cdr();
    sexpr cadr();
    sexpr cdar();

    llvm::Value *generate(llvm::IRBuilder<> &builder, llvm::BasicBlock *entry);

    operator minivar_t& ();
};

} // namespace sx

#endif // SX_SEXPR_H
