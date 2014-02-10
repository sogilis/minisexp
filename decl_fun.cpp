#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>

#include <iostream>

#include "decl_fun.h"

namespace sx {
namespace decl {

fun::fun(std::string name, sexpr expr) : name(name), sexpr(expr)
{
    std::cerr << "fun " << expr.to_string() << std::endl;

    if(car().to_name() != "fun") {
        throw std::string("expected fun, got " + car().to_string());
    }
}

sexpr fun::instr_list()
{
    return cdr();
}

void fun::generate(llvm::Module *module)
{
    llvm::IRBuilder<> builder(module->getContext());

    llvm::FunctionType *funcType =
        llvm::FunctionType::get(builder.getVoidTy(), false);
    llvm::Function *mainFunc =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name, module);

    std::vector<llvm::Type*> putsFuncTypeArgs(1);
    putsFuncTypeArgs[0] = builder.getInt8PtrTy();
    llvm::FunctionType *putsFuncType =
        llvm::FunctionType::get(builder.getVoidTy(), llvm::makeArrayRef(putsFuncTypeArgs), false);
    llvm::Function *putsFunc =
        llvm::Function::Create(putsFuncType, llvm::Function::ExternalLinkage, "puts", module);

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entry", mainFunc);
    builder.SetInsertPoint(entry);

    sexpr i = instr_list();
    while(!i.is_nil()) {
        sexpr call = i.car();
        std::string fname = call.car().to_name();
        if(fname == "puts") {
            std::vector<llvm::Value*> putsFuncArgs(1);
            putsFuncArgs[0] = call.cdr().car().generate(builder);
            llvm::CallInst::Create(putsFunc, llvm::makeArrayRef(putsFuncArgs), "", entry);
        }
        i = i.cdr();
    }

    llvm::ReturnInst::Create(module->getContext(), entry);
    builder.SetInsertPoint(entry);
}

} // namespace decl
} // namespace sx
