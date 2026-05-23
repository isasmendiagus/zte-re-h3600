// module: mt7915.ko
// function: MtCmdGetTxSmeshRsp @ 0x1ab3a0
// size: 24 bytes
//

void MtCmdGetTxSmeshRsp(int param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 0xc);
  *puVar1 = *param_2;
  *(undefined4 *)(puVar1 + 4) = *(undefined4 *)(param_2 + 4);
  return;
}

