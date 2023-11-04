#include "RRISCVTargetMachine.h"
#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/MC/MCStreamer.h>
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

namespace llvm {
class RRISCVAsmPrinter : public AsmPrinter {
public:
  RRISCVAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  virtual StringRef getPassName() const override { return "RRISCV Assembly Printer"; }
};
} // namespace llvm

extern Target TheRRISCVTarget;

extern "C" void LLVMInitializeRRISCVAsmPrinter() {
  RegisterAsmPrinter<RRISCVAsmPrinter> X(TheRRISCVTarget);
}