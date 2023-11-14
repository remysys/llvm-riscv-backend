#include "RRISCVAsmPrinter.h"
#include "RRISCVMCInstLower.h"
#include "RRISCVTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/MC/MCStreamer.h>

using namespace llvm;

#include "RRISCVGenMCPseudoLowering.inc"
void RRISCVAsmPrinter::emitInstruction(const MachineInstr *MI) {
  if (emitPseudoExpansionLowering(*OutStreamer, MI)) {
    return;
  }

  MachineBasicBlock::const_instr_iterator I = MI->getIterator();
  MachineBasicBlock::const_instr_iterator E = MI->getParent()->instr_end();

  do {
    MCInst TmpMCInst;
    MCInstLowering.Lower(&*I, TmpMCInst);
    OutStreamer->emitInstruction(TmpMCInst, getSubtargetInfo());
  } while (++I != E && I->isInsideBundle());
}

extern Target TheRRISCVTarget;

extern "C" void LLVMInitializeRRISCVAsmPrinter() {
  RegisterAsmPrinter<RRISCVAsmPrinter> X(TheRRISCVTarget);
}