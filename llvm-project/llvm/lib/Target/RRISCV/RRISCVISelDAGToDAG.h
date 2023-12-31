#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVISELDAGTODAG_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVISELDAGTODAG_H

#include "RRISCVTargetMachine.h"
#include <llvm/CodeGen/SelectionDAGISel.h>
#include "TargetDesc/RRISCVTargetDesc.h"

namespace llvm {
class RRISCVDAGToDAGISel : public SelectionDAGISel {
public:
  explicit RRISCVDAGToDAGISel(RRISCVTargetMachine &TargetMachine,
                             CodeGenOpt::Level OptLevel)
      : SelectionDAGISel(TargetMachine, OptLevel) {}

  StringRef getPassName() const override {
    return "RRISCV DAG->DAG Pattern Instruction Selection";
  }

  void Select(SDNode *N) override;
  bool SelectAddrFI(SDNode *Parent, SDValue N, SDValue &Base, SDValue &Offset);
  
  #include "RRISCVGenDAGISel.inc"
};


} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVISELDAGTODAG_H