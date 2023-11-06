#include "RRISCVTargetMachine.h"
#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/MC/MCStreamer.h>
#include "llvm/MC/TargetRegistry.h"
#include "RRISCVMCInstLower.h"
using namespace llvm;

namespace llvm {
class MachineInstr;
class RRISCVAsmPrinter : public AsmPrinter {
private:
  RRISCVMCInstLower MCInstLowering;
public:
  RRISCVAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  virtual StringRef getPassName() const override { return "RRISCV Assembly Printer"; }
  void emitInstruction(const MachineInstr *MI) override;
};
} // namespace llvm

void RRISCVAsmPrinter::emitInstruction(const MachineInstr *MI) {
  MachineBasicBlock::const_instr_iterator I = MI->getIterator();
  MachineBasicBlock::const_instr_iterator E = MI->getParent()->instr_end();

  do {
    MCInst TmpMCInst;
    MCInstLowering.Lower(&*I, TmpMCInst);
    OutStreamer->emitInstruction(TmpMCInst, getSubtargetInfo());
  } while (++I != E);
}

extern Target TheRRISCVTarget;

extern "C" void LLVMInitializeRRISCVAsmPrinter() {
  RegisterAsmPrinter<RRISCVAsmPrinter> X(TheRRISCVTarget);
}