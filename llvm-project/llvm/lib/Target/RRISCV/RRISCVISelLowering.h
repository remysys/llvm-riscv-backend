#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVISELLOWERING_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVISELLOWERING_H

#include <llvm/CodeGen/SelectionDAG.h>
#include <llvm/CodeGen/TargetLowering.h>

namespace llvm {
namespace RRISCVISD {
enum NodeType {
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  Hi,
  Lo,
  Ret,
  Call,
};
}
class RRISCVSubtarget;
class RRISCVTargetLowering : public TargetLowering {
private:
  SDValue lowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;
  SDValue lowerConstantPool(SDValue Op, SelectionDAG &DAG) const;
  const RRISCVSubtarget &Subtarget;

public:
  RRISCVTargetLowering(const TargetMachine &TM, const RRISCVSubtarget &STI);

  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;

  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
                      SelectionDAG &DAG) const override;
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  const char *getTargetNodeName(unsigned Opcode) const override;

  SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
                    SmallVectorImpl<SDValue> &InVals) const override;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVISELLOWERING_H