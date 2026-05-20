// module: mt7915.ko
// function: MtCmdGetTsfTimeRsp @ 0x1ab418
// size: 24 bytes
//

void MtCmdGetTsfTimeRsp(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0xc);
  *puVar1 = *(undefined4 *)(param_2 + 4);
  puVar1[1] = *(undefined4 *)(param_2 + 8);
  return;
}

