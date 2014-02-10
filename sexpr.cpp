#include <sstream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>

#include "sexpr.h"
#include "io.h"

namespace sx {

sexpr::sexpr(minivar_t expr) : expr(expr)
{
}

sexpr::sexpr(sexpr &expr) : expr(expr.expr)
{

}

std::string sexpr::to_string()
{
    std::stringstream s;
    streamio io(&s);

    miniexp_print_r(io.get_io(), expr);

    return s.str();
}

bool sexpr::is_nil()
{
    return miniexp_nil == expr;
}

bool sexpr::is_string()
{
    return miniexp_stringp(expr);
}

std::string sexpr::to_name()
{
    const char *s = miniexp_to_name(expr);
    if(s) return s;
    return std::string();
}

void sexpr::print()
{
    miniexp_print(expr);
}

sexpr sexpr::car()
{
    return sexpr(miniexp_car(expr));
}

sexpr sexpr::cdr()
{
    return sexpr(miniexp_cdr(expr));
}

sexpr sexpr::cadr()
{
    return sexpr(miniexp_cadr(expr));
}

sexpr sexpr::cdar()
{
    return sexpr(miniexp_cdar(expr));
}

llvm::Value *sexpr::generate(llvm::IRBuilder<> &builder, llvm::BasicBlock *entry)
{
    if(is_string()) {
        return builder.CreateGlobalStringPtr(to_string());
    } else if(miniexp_numberp(expr)) {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(builder.getContext()), miniexp_to_int(expr));
    } else if(miniexp_listp(expr)) {
        std::string fname = car().to_name();
        if(fname == "+") {
            return llvm::BinaryOperator::Create(llvm::Instruction::Add, cdr().car().generate(builder, entry), cdr().cdr().car().generate(builder, entry), "", entry);
        } else {
            throw std::string("unsupported function " + car().to_string());
        }
    } else {
        throw std::string("unsupported instruction " + to_string());
    }
}

sx::sexpr::operator minivar_t&()
{
    return expr;
}

} // namespace sx
