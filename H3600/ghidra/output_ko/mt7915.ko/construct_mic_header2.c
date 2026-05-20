// module: mt7915.ko
// function: construct_mic_header2 @ 0xb65c4
// size: 264 bytes
//

void construct_mic_header2(undefined1 *param_1,int param_2,uint param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar3 = param_1 + -1;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != param_1 + 0xf);
  uVar2 = 0;
  if (param_4 == 0) {
    uVar2 = param_3 & 1;
  }
  *param_1 = *(undefined1 *)(param_2 + 0x10);
  param_1[1] = *(undefined1 *)(param_2 + 0x11);
  param_1[2] = *(undefined1 *)(param_2 + 0x12);
  param_1[3] = *(undefined1 *)(param_2 + 0x13);
  param_1[4] = *(undefined1 *)(param_2 + 0x14);
  param_1[5] = *(undefined1 *)(param_2 + 0x15);
  bVar1 = *(byte *)(param_2 + 0x16);
  param_1[7] = 0;
  param_1[6] = bVar1 & 0xf;
  if (uVar2 != 0) {
    puVar3 = (undefined1 *)(param_2 + 0x17);
    puVar4 = param_1 + 7;
    do {
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
      *puVar4 = *puVar3;
    } while (puVar3 != (undefined1 *)(param_2 + 0x1d));
  }
  if (param_3 == 0 && param_4 != 0) {
    bVar1 = *(byte *)(param_2 + 0x18);
    param_1[9] = 0;
    param_1[8] = bVar1 & 0xf;
  }
  if (param_3 != 0 && param_4 != 0) {
    puVar4 = (undefined1 *)(param_2 + 0x17);
    puVar3 = param_1 + 7;
    do {
      puVar4 = puVar4 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar4;
    } while (puVar4 != (undefined1 *)(param_2 + 0x1d));
    bVar1 = *(byte *)(param_2 + 0x1e);
    param_1[0xf] = 0;
    param_1[0xe] = bVar1 & 0xf;
    return;
  }
  return;
}

