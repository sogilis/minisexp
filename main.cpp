#include <stdio.h>
#include <iostream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/PassManager.h>
#include <llvm/Support/raw_ostream.h>

#include "miniexp.h"
#include "sexpr.h"
#include "decls_def.h"

#define FAIL(msg) { std::cerr << msg << std::endl; return 1; }

static inline std::string miniexp_to_stdstr(miniexp_t p) {
    const char *s =  miniexp_to_str(p);
    if(s) return std::string(s);
    return std::string();
}
static inline std::string miniexp_to_stdname(miniexp_t p) {
    const char *s =  miniexp_to_name(p);
    if(s) return std::string(s);
    return std::string();
}

using namespace std;

namespace sx {
void declare_fun(llvm::Module* module, minivar_t name, minivar_t code) {
    llvm::IRBuilder<> builder(module->getContext());

    llvm::FunctionType *funcType =
        llvm::FunctionType::get(builder.getVoidTy(), false);
    llvm::Function *mainFunc =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, miniexp_to_name(name), module);

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entry", mainFunc);
    llvm::ReturnInst::Create(module->getContext(), entry);
    builder.SetInsertPoint(entry);
}

void declare(llvm::Module* module, minivar_t declare_list) {
    minivar_t name = miniexp_car(declare_list);
    minivar_t object = miniexp_cadr(declare_list);

    minivar_t objecttype = miniexp_car(object);
    if(miniexp_to_stdname(objecttype) == "fun") {
        declare_fun(module, name, miniexp_cadr(declare_list));
    } else {
        std::cerr << "Unknown object type " << miniexp_to_stdname(objecttype) << " to declare " << miniexp_to_stdname(name) << std::endl;
        return;
    }
}
}

int main(int argc, char *argv[])
{
    //try {
        llvm::LLVMContext& context = llvm::getGlobalContext();

        // We are building a module
        llvm::Module* module = new llvm::Module("top", context);

        minilisp_set_output(stderr);
        minilisp_set_input(stdin);

        while(1) {
            minivar_t s = miniexp_read();
            if (s == miniexp_dummy) {
                if(feof(stdin)) {
                    std::cerr << "end of stream." << std::endl;
                    break;
                } else {
                    std::cerr << "Error during parsing." << std::endl;
                    return 1;
                }
            }

            sx::sexpr se(s);
            sx::decl::def definition(se);
            definition.print();

            std::cerr << "generate..." << std::endl;

            definition.generate(module);


            /*
        ss.print();



        if(!miniexp_listp(s)) FAIL("expected list");
        if(!miniexp_length(s)) FAIL("expected on empty list");

        sx::decl::def name(ss.car());
        def.generate(module);
        if(name.to_name() != "def") FAIL("expected def got " << name.to_name());
        sx::declare(module, miniexp_cdr(s));
        */
        }

        llvm::PassManager pm;
        pm.add(llvm::createPrintModulePass(&llvm::outs()));
        pm.run(*module);

        //module->dump();
    //} catch (std::string &s) {
    //    std::cerr << "Exception std::string: " << s << std::endl;
    //    abort();
    //}
}
