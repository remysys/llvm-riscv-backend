def CSR : CalleeSavedRegs<(add RA, S0, S1)>;
def RRISCVCC : CallingConv<[
    CCIfType<[i32], CCAssignToReg<[A0, A1]>>,
    CCAssignToStack<4, 4>
]>;