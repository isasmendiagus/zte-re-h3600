// module: mt7915.ko
// function: TxBfProfileTag_Mem @ 0x86878
// size: 68 bytes
//

void TxBfProfileTag_Mem(int param_1,undefined1 *param_2,byte *param_3)

{
  *(undefined1 *)(param_1 + 0x14) = *param_2;
  *(ushort *)(param_1 + 0xc) = (ushort)*param_3;
  *(undefined1 *)(param_1 + 0x15) = param_2[1];
  *(ushort *)(param_1 + 0xe) = (ushort)param_3[1];
  *(undefined1 *)(param_1 + 0x16) = param_2[2];
  *(ushort *)(param_1 + 0x10) = (ushort)param_3[2];
  *(undefined1 *)(param_1 + 0x17) = param_2[3];
  *(ushort *)(param_1 + 0x12) = (ushort)param_3[3];
  return;
}

