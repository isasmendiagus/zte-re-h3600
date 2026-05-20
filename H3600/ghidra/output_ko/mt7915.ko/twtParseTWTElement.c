// module: mt7915.ko
// function: twtParseTWTElement @ 0x168a7c
// size: 100 bytes
//

void twtParseTWTElement(int param_1,byte *param_2)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar1 = *(ushort *)(param_1 + 3);
  uVar2 = (uint)uVar1;
  *param_2 = (byte)uVar1 & 1;
  param_2[4] = (byte)((uVar2 << 0x1c) >> 0x1d);
  param_2[1] = (byte)((uVar2 << 0x1b) >> 0x1f);
  param_2[3] = (byte)((uVar2 << 0x19) >> 0x1f);
  param_2[6] = (byte)((uVar2 << 0x11) >> 0x1b);
  param_2[2] = (byte)(uVar1 >> 0xf);
  uVar3 = *(undefined4 *)(param_1 + 9);
  *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 5);
  *(undefined4 *)(param_2 + 0x14) = uVar3;
  param_2[5] = *(byte *)(param_1 + 0xd);
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_1 + 0xe);
  return;
}

