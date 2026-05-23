// module: mt7915.ko
// function: construct_ctr_preload @ 0xb68ec
// size: 180 bytes
//

void construct_ctr_preload
               (undefined1 *param_1,int param_2,int param_3,int param_4,undefined1 *param_5,
               int param_6)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = param_1 + -1;
  do {
    puVar2 = puVar2 + 1;
    *puVar2 = 0;
  } while (puVar2 != param_1 + 0xf);
  *param_1 = 1;
  if (param_2 != 0 && param_3 != 0) {
    param_1[1] = *(byte *)(param_4 + 0x1e) & 0xf;
  }
  puVar2 = param_1 + 1;
  if (param_2 == 0 && param_3 != 0) {
    param_1[1] = *(byte *)(param_4 + 0x18) & 0xf;
  }
  puVar1 = (undefined1 *)(param_4 + 9);
  do {
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
    *puVar2 = *puVar1;
  } while (puVar1 != (undefined1 *)(param_4 + 0xf));
  puVar1 = param_5 + 6;
  puVar2 = param_1 + 7;
  do {
    puVar1 = puVar1 + -1;
    puVar2 = puVar2 + 1;
    *puVar2 = *puVar1;
  } while (puVar1 != param_5);
  param_1[0xf] = (char)param_6;
  if (param_6 < 0) {
    param_6 = param_6 + 0xff;
  }
  param_1[0xe] = (char)((uint)param_6 >> 8);
  return;
}

