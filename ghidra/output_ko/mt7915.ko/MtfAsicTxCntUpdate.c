// module: mt7915.ko
// function: MtfAsicTxCntUpdate @ 0x1958e0
// size: 92 bytes
//

void MtfAsicTxCntUpdate(undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  ushort local_18;
  ushort local_16;
  ushort local_14;
  ushort local_12;
  
  FUN_0019510c(param_1,param_2,&local_20);
  *(undefined2 *)(param_3 + 2) = local_20;
  *param_3 = (uint)local_14 + (uint)local_18;
  *(undefined2 *)((int)param_3 + 10) = local_1e;
  param_3[1] = (uint)local_12 + (uint)local_16;
  *(undefined2 *)(param_3 + 3) = local_1c;
  *(undefined2 *)((int)param_3 + 0xe) = local_1a;
  return;
}

