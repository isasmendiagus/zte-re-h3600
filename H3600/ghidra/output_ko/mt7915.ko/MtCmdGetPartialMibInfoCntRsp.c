// module: mt7915.ko
// function: MtCmdGetPartialMibInfoCntRsp @ 0x1ab430
// size: 88 bytes
//

void MtCmdGetPartialMibInfoCntRsp(int param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 0xc);
  *puVar1 = *(undefined1 *)(param_2 + 4);
  *(undefined4 *)(puVar1 + 4) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(puVar1 + 8) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(puVar1 + 0xc) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(puVar1 + 0x10) = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(puVar1 + 0x14) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(puVar1 + 0x18) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(puVar1 + 0x1c) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(puVar1 + 0x20) = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(puVar1 + 0x24) = *(undefined4 *)(param_2 + 0x28);
  return;
}

