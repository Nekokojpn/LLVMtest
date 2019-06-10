#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value *> NamedValues;



int main(int argc, char **argv) {
  if (argc != 2)
		std::cerr << "Insufficient arguments." << std::endl;
  double x = atoi(&argv[1][0]);
  char op = argv[1][1];
  double y = atoi(&argv[1][2]);
  std::cout << x << op << y << std::endl;

  /*
  Value* L = ConstantFP::get(TheContext,APFloat(x));
  Value *R = ConstantFP::get(TheContext, APFloat(y));
  Builder.CreateFAdd(L, R, "addtmp");

  Function *CalleeF = TheModule->getFunction("main");
  if (!CalleeF)
		 std::cerr << "Unknown function referenced\n";
*/
  TheModule = llvm::make_unique<Module>("top", TheContext);
  Function *mainFunc =
      Function::Create(FunctionType::get(Type::getInt32Ty(TheContext), false),
                       Function::ExternalLinkage, "main", TheModule.get());
  Builder.SetInsertPoint(BasicBlock::Create(TheContext, "", mainFunc));

  Value *Vx = Builder.CreateAlloca(Builder.getInt32Ty(), nullptr, "x");
  Value *Vy = Builder.CreateAlloca(Builder.getInt32Ty(), nullptr, "y");
  Builder.CreateStore(Builder.getInt32(x), Vx);
  Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(Vx),Builder.CreateLoad(Vy)),Vy);

  Builder.CreateRet(Builder.CreateAdd(Builder.CreateLoad(Vx),Builder.CreateLoad(Vy)));

  TheModule->dump();
}