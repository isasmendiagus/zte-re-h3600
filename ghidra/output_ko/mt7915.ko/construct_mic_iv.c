// module: mt7915.ko
// function: construct_mic_iv @ 0xb66cc
// size: 160 bytes
//

void construct_mic_iv(undefined1 *param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                     undefined1 *param_6)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  *param_1 = 0x59;
  if (param_3 != 0 && param_2 != 0) {
    param_1[1] = *(byte *)(param_4 + 0x1e) & 0xf;
  }
  if (param_3 == 0 && param_2 != 0) {
    param_1[1] = *(byte *)(param_4 + 0x18) & 0xf;
  }
  else if (param_2 == 0) {
    param_1[1] = 0;
  }
  puVar2 = (undefined1 *)(param_4 + 9);
  puVar1 = param_1 + 1;
  do {
    puVar2 = puVar2 + 1;
    puVar1 = puVar1 + 1;
    *puVar1 = *puVar2;
  } while (puVar2 != (undefined1 *)(param_4 + 0xf));
  puVar2 = param_6 + 6;
  puVar1 = param_1 + 7;
  do {
    puVar2 = puVar2 + -1;
    puVar1 = puVar1 + 1;
    *puVar1 = *puVar2;
  } while (puVar2 != param_6);
  param_1[0xf] = (char)param_5;
  param_1[0xe] = (char)((uint)param_5 >> 8);
  return;
}

