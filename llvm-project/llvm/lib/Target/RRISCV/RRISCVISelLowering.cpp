#include "RRISCVISelLowering.h"
#include "RRISCVSubtarget.h"
#include "TargetDesc/RRISCVBaseInfo.h"
#include "TargetDesc/RRISCVTargetDesc.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

RRISCVTargetLowering::RRISCVTargetLowering(const TargetMachine &TM,
                                           const RRISCVSubtarget &STI)
    : TargetLowering(TM) {
  addRegisterClass(MVT::i32, &RRISCV::GPRRegClass);
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
  // expand br_cc to setcc and brcond instructions
  setOperationAction(ISD::BR_CC, MVT::i32, Expand);
  computeRegisterProperties(STI.getRegisterInfo());
}

#include "RRISCVGenCallingConv.inc"
void analyzeFormalArguments(const SmallVectorImpl<ISD::InputArg> &Args,
                            CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

void analyzeCallOperands(const SmallVectorImpl<ISD::OutputArg> &Args,
                         CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

void analyzeReturn(const SmallVectorImpl<ISD::OutputArg> &Args,
                   CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

SDValue RRISCVTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  MachineFunction &MF = DAG.getMachineFunction();

  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), ArgLocs,
                 *DAG.getContext());

  analyzeFormalArguments(Ins, CCInfo);
  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    assert(VA.isRegLoc());
    MVT RegVT = VA.getLocVT();
    unsigned ArgReg = VA.getLocReg();
    const TargetRegisterClass *RC = getRegClassFor(RegVT);

    unsigned VReg = MF.getRegInfo().createVirtualRegister(RC);
    MF.getRegInfo().addLiveIn(ArgReg, VReg);
    SDValue ArgValue = DAG.getCopyFromReg(Chain, DL, VReg, RegVT);
    InVals.push_back(ArgValue);
  }
  return Chain;
}

SDValue
RRISCVTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                  bool IsVarArg,
                                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                                  const SmallVectorImpl<SDValue> &OutVals,
                                  const SDLoc &DL, SelectionDAG &DAG) const {
  SmallVector<CCValAssign, 2> RVLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());
  analyzeReturn(Outs, CCInfo);
  for (unsigned i = 0, e = RVLocs.size(); i != e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc());
    unsigned RVReg = VA.getLocReg();
    Chain = DAG.getCopyToReg(Chain, DL, RVReg, OutVals[i]);
  }
  SmallVector<SDValue, 4> Ops(1, Chain);
  Ops[0] = Chain;
  return DAG.getNode(RRISCVISD::Ret, DL, MVT::Other, Ops);
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
  int64_t Offset = N->getOffset();
  SDLoc DL(N);
  SDValue Hi =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_HI);
  SDValue Lo =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_LO);
  // return DAG.getNode(ISD::ADD, DL, Ty, DAG.getNode(RRISCVISD::Hi, DL, Ty,
  // Hi), DAG.getNode(RRISCVISD::Lo, DL, Ty, Lo));
  SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);
  // return SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);

  SDValue Addr = SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);
  if (Offset != 0) {
    return DAG.getNode(ISD::ADD, DL, Ty, Addr, DAG.getConstant(Offset, DL, Ty));
  }
  return Addr;
}

const char *RRISCVTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case RRISCVISD::Hi:
    return "RRISCVISD::Hi";
  case RRISCVISD::Lo:
    return "RRISCVISD::Lo";
  case RRISCVISD::Ret:
    return "RRISCVISD::Ret";
  default:
    return NULL;
  }
}

SDValue
RRISCVTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                SmallVectorImpl<SDValue> &InVals) const {
  SelectionDAG &DAG = CLI.DAG;
  SDLoc DL = CLI.DL;
  SDValue Chain = CLI.Chain;
  SDValue Callee = CLI.Callee;

  CallingConv::ID CallConv = CLI.CallConv;
  bool IsVarArg = CLI.IsVarArg;

  SmallVectorImpl<ISD::OutputArg> &Outs = CLI.Outs;
  SmallVectorImpl<SDValue> &OutVals = CLI.OutVals;

  SmallVector<CCValAssign, 2> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), ArgLocs,
                 *DAG.getContext());
  analyzeCallOperands(Outs, CCInfo);
  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    assert(VA.isRegLoc());
    unsigned ArgReg = VA.getLocReg();
    Chain = DAG.getCopyToReg(Chain, DL, ArgReg, OutVals[i]);
  }

  GlobalAddressSDNode *N = dyn_cast<GlobalAddressSDNode>(Callee);

  EVT Ty = getPointerTy(DAG.getDataLayout());
  SDValue Hi =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_HI);
  SDValue Lo =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_LO);
  SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);

  Callee = SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);

  SmallVector<SDValue, 8> Ops(1, Chain);
  Ops.push_back(Callee);
  SDVTList NodeTys = DAG.getVTList(MVT::Other, MVT::Glue);
  Chain = DAG.getNode(RRISCVISD::Call, DL, NodeTys, Ops);

  {
    SmallVector<CCValAssign, 2> RVLocs;
    CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                   *DAG.getContext());

    analyzeReturn(Outs, CCInfo);
    for (unsigned i = 0, e = RVLocs.size(); i != e; ++i) {
      CCValAssign &VA = RVLocs[i];
      assert(VA.isRegLoc());
      unsigned RVReg = VA.getLocReg();
      SDValue Val = DAG.getCopyFromReg(Chain, DL, RVReg, RVLocs[i].getLocVT());
      InVals.push_back(Val);
    }
  }

  return Chain;
}