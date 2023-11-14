#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVASMPRINTER_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVASMPRINTER_H

#include "RRISCVMCInstLower.h"
#include "RRISCVTargetMachine.h"
#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/MC/MCStreamer.h>

namespace llvm {
class MachineInstr;
class RRISCVAsmPrinter : public AsmPrinter {
private:
  RRISCVMCInstLower MCInstLowering;

public:
  RRISCVAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), MCInstLowering(*this) {}

  virtual StringRef getPassName() const override {
    return "rriscv asm printer";
  }
  void emitInstruction(const MachineInstr *MI) override;
  bool emitPseudoExpansionLowering(MCStreamer &OutStreamer,
                                   const MachineInstr *MI);
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVASMPRINTER_H