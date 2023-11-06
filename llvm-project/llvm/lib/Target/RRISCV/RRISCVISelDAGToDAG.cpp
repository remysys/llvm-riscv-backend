#include "RRISCVISelDAGToDAG.h"

using namespace llvm;

void RRISCVDAGToDAGISel::Select(SDNode *N) { SelectCode(N); }

bool RRISCVDAGToDAGISel::SelectAddrFI(SDNode *Parent, SDValue Addr, SDValue &Base,
                                   SDValue &Offset) {
  EVT ValTy = Addr.getValueType();
  SDLoc DL(Addr);
  if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Addr)) {
    Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
    Offset = CurDAG->getTargetConstant(0, DL, ValTy);
    return true;
  }
  return false;
}