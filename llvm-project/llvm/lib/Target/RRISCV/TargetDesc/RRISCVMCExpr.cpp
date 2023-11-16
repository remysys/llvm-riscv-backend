#include "RRISCVMCExpr.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void RRISCVMCExpr::printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const {

  switch (Kind) {
  default:
    llvm_unreachable("kind is invalid");
    break;
  case TEK_HI:
    OS << "%hi";
    break;
  case TEK_LO:
    OS << "%lo";
    break;
  }

  OS << '(';
  Expr->print(OS, MAI, true);
  OS << ')';
}