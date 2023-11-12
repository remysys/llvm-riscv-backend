#include "RRISCVISelLowering.h"
#include "TargetDesc/RRISCVBaseInfo.h"
#include "TargetDesc/RRISCVTargetDesc.h"

using namespace llvm;

RRISCVTargetLowering::RRISCVTargetLowering(const TargetMachine &TM,
                                           const RRISCVSubtarget &STI)
    : TargetLowering(TM) {
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
}

SDValue RRISCVTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  return Chain;
}

SDValue
RRISCVTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                  bool IsVarArg,
                                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                                  const SmallVectorImpl<SDValue> &OutVals,
                                  const SDLoc &DL, SelectionDAG &DAG) const {
  return Chain;
}

SDValue RRISCVTargetLowering::LowerOperation(SDValue Op,
                                             SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::GlobalAddress:
    return lowerGlobalAddress(Op, DAG);
  }
  return SDValue();
}

SDValue RRISCVTargetLowering::lowerGlobalAddress(SDValue Op,
                                                 SelectionDAG &DAG) const {
  EVT Ty = Op.getValueType();
  GlobalAddressSDNode *N = cast<GlobalAddressSDNode>(Op);
  SDLoc DL(N);
  SDValue Hi =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_HI);
  SDValue Lo =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_LO);
  // return DAG.getNode(ISD::ADD, DL, Ty, DAG.getNode(RRISCVISD::Hi, DL, Ty,
  // Hi), DAG.getNode(RRISCVISD::Lo, DL, Ty, Lo));
  SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);
  return SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);
}

const char *RRISCVTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case RRISCVISD::Hi:
    return "RRISCVISD::Hi";
  case RRISCVISD::Lo:
    return "RRISCVISD::Lo";
  default:
    return NULL;
  }
}