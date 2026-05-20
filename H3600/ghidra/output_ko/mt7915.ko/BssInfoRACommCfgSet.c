// module: mt7915.ko
// function: BssInfoRACommCfgSet @ 0x1d9370
// size: 204 bytes
//

undefined4 BssInfoRACommCfgSet(undefined1 *param_1,undefined2 *param_2)

{
  param_2[1] = 0x2c;
  *param_2 = 10;
  *(undefined1 *)(param_2 + 2) = *param_1;
  *(undefined1 *)((int)param_2 + 5) = param_1[1];
  *(undefined1 *)(param_2 + 3) = param_1[2];
  *(undefined1 *)((int)param_2 + 7) = param_1[3];
  *(undefined1 *)(param_2 + 4) = param_1[4];
  *(undefined1 *)((int)param_2 + 9) = param_1[5];
  *(undefined1 *)(param_2 + 5) = param_1[6];
  *(undefined1 *)((int)param_2 + 0xb) = param_1[7];
  *(undefined1 *)(param_2 + 6) = param_1[8];
  *(undefined1 *)((int)param_2 + 0xd) = param_1[9];
  *(undefined1 *)(param_2 + 7) = param_1[10];
  *(undefined1 *)((int)param_2 + 0xf) = param_1[0xb];
  *(undefined1 *)(param_2 + 9) = param_1[0xf];
  *(undefined1 *)((int)param_2 + 0x13) = param_1[0x10];
  *(undefined1 *)(param_2 + 10) = param_1[0x11];
  param_2[0xc] = *(undefined2 *)(param_1 + 0x12);
  param_2[0xd] = *(undefined2 *)(param_1 + 0x14);
  param_2[0xe] = *(undefined2 *)(param_1 + 0x16);
  param_2[0xf] = *(undefined2 *)(param_1 + 0x18);
  *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_2 + 0x12) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_1 + 0x24);
  return 0;
}

