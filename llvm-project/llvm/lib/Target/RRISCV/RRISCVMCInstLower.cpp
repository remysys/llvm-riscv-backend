#include "RRISCVMCInstLower.h"
#include "RRISCVAsmPrinter.h"
#include "TargetDesc/RRISCVBaseInfo.h"
#include "TargetDesc/RRISCVMCExpr.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

void RRISCVMCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const {
  OutMI.setOpcode(MI->getOpcode());

  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    MCOperand MCOp = LowerOperand(MO);
    if (MCOp.isValid()) {
      OutMI.addOperand(MCOp);
    }
  }
}

MCOperand
RRISCVMCInstLower::LowerSymbolOperand(const MachineOperand &MO) const {
  MCContext &Ctx = AsmPrinter.OutContext;
  RRISCVMCExpr::RRISCVExprKind TargetKind = RRISCVMCExpr::TEK_NONE;
  const MCSymbol *Symbol;

  switch (MO.getTargetFlags()) {
  default:
    llvm_unreachable("Invalid target flag!");
  case RRISCVII::MO_NO_FLAG:
    break;
  case RRISCVII::MO_HI:
    TargetKind = RRISCVMCExpr::TEK_HI;
    break;
  case RRISCVII::MO_LO:
    TargetKind = RRISCVMCExpr::TEK_LO;
    break;
  }

  switch (MO.getType()) {
  case MachineOperand::MO_GlobalAddress:
    Symbol = AsmPrinter.getSymbol(MO.getGlobal());
    break;
  default:
    llvm_unreachable("<unknown operand type>");
  }

  const MCExpr *Expr =
      MCSymbolRefExpr::create(Symbol, MCSymbolRefExpr::VK_None, Ctx);
  Expr = new RRISCVMCExpr(TargetKind, Expr);

  return MCOperand::createExpr(Expr);
}

MCOperand RRISCVMCInstLower::LowerOperand(const MachineOperand &MO) const {
  switch (MO.getType()) {
  default:
    llvm_unreachable("unknown operand type");
  case MachineOperand::MO_Register:
    return MCOperand::createReg(MO.getReg());
  case MachineOperand::MO_Immediate:
    return MCOperand::createImm(MO.getImm());
  case MachineOperand::MO_GlobalAddress:
    return LowerSymbolOperand(MO);
  }

  return MCOperand();
}