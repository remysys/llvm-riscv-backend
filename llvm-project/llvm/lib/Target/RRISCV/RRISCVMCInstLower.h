#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVMCINSTLOWER_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVMCINSTLOWER_H

namespace llvm {
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class RRISCVAsmPrinter;
class RRISCVMCInstLower {
private:
  RRISCVAsmPrinter &AsmPrinter;
  MCOperand LowerSymbolOperand(const MachineOperand &MO, int IsBranch) const;

public:
  RRISCVMCInstLower(RRISCVAsmPrinter &printer) : AsmPrinter(printer){};
  void Lower(const MachineInstr *MI, MCInst &OutMI) const;
  MCOperand LowerOperand(const MachineOperand &MO, int IsBranch) const;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVMCINSTLOWER_H