// module: mt7915.ko
// function: MlmeSetPsmBit @ 0x129ff0
// size: 52 bytes
//

void MlmeSetPsmBit(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = DebugLevel;
  *(short *)(param_2 + 0x2124b8) = (short)param_3;
  if (iVar1 < 3) {
    return;
  }
  printk("MlmeSetPsmBit = %d\n",param_3);
  return;
}

