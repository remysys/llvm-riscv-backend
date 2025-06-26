#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCEXPR_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCEXPR_H

#include "llvm/MC/MCAsmLayout.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCValue.h"

namespace llvm {
class RRISCVMCExpr : public MCTargetExpr {
public:
  enum RRISCVExprKind { TEK_NONE, TEK_HI, TEK_LO, TEK_JAL, TEK_BRANCH };
  RRISCVMCExpr(RRISCVExprKind Kind, const MCExpr *Expr)
      : Kind(Kind), Expr(Expr) {}

  void printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const override;

  bool evaluateAsRelocatableImpl(MCValue &Res, const MCAsmLayout *Layout,
                                 const MCFixup *Fixup) const override;
  void visitUsedExpr(MCStreamer &Streamer) const override {
    Streamer.visitUsedExpr(*Expr);
  }

  MCFragment *findAssociatedFragment() const override { return NULL; }
  void fixELFSymbolsInTLSFixups(MCAssembler &Asm) const override {};

  const MCExpr *getSubExpr() const { return Expr; }
  RRISCVExprKind getKind() const { return Kind; }

private:
  const RRISCVExprKind Kind;
  const MCExpr *Expr;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCEXPR_H