#include <exception>
#include <iostream>
#include "decls_def.h"
#include "decl_fun.h"

namespace sx {
namespace decl {

def::def(sexpr expr) : sexpr(expr)
{
    std::cerr << "def " << expr.to_string() << std::endl;

    if(car().to_name() != "def") {
        throw std::string("expected def, got " + car().to_string());
    }
}

sexpr def::declare_list()
{
    return cdr().cdr().car();
}

sexpr def::declare_name()
{
    return cdr().car();
}

void def::generate(llvm::Module *module)
{
    std::string type = declare_list().car().to_name();

    if(type == "fun") {
        declare_name().print();
        fun decl(declare_name().to_name(), declare_list());
        decl.generate(module);
    } else {
        throw std::string("expected fun, got " + declare_list().car().to_string());
    }
}

} // namespace decl
} // namespace sx
