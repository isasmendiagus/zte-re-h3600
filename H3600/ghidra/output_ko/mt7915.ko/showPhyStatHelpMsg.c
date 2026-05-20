// module: mt7915.ko
// function: showPhyStatHelpMsg @ 0x34a24
// size: 36 bytes
//

void showPhyStatHelpMsg(int param_1,code *param_2)

{
  int iVar1;
  
  iVar1 = (*param_2)(*(undefined4 *)(param_1 + 0x10),0x2800);
  if (iVar1 != 0) {
    *(short *)(param_1 + 0x14) = (short)iVar1;
  }
  return;
}

