// module: mt7915.ko
// function: StaRecAutoRateParamSet @ 0x1d943c
// size: 388 bytes
//

undefined4 StaRecAutoRateParamSet(char *param_1,undefined2 *param_2)

{
  char cVar1;
  uint uVar2;
  
  *param_2 = 1;
  param_2[1] = 0x38;
  cVar1 = *param_1;
  *(char *)(param_2 + 2) = cVar1;
  *(char *)((int)param_2 + 5) = param_1[4];
  if (cVar1 != '\0') {
    *(char *)(param_2 + 3) = param_1[5];
    *(char *)((int)param_2 + 7) = param_1[6];
    *(char *)(param_2 + 4) = param_1[7];
    *(char *)((int)param_2 + 9) = param_1[8];
    *(char *)(param_2 + 5) = param_1[9];
    *(char *)((int)param_2 + 0xb) = param_1[10];
    os_move_mem(param_2 + 6,param_1 + 0xb,4);
    *(char *)(param_2 + 8) = param_1[0xf];
    *(char *)((int)param_2 + 0x11) = param_1[0x15];
    *(char *)(param_2 + 9) = param_1[0x16];
    *(char *)((int)param_2 + 0x13) = param_1[0x42];
    *(char *)(param_2 + 10) = param_1[0x17];
    *(char *)((int)param_2 + 0x15) = param_1[0x18];
    *(char *)(param_2 + 0xb) = param_1[0x19];
    *(char *)((int)param_2 + 0x17) = param_1[0x1a];
    *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(param_1 + 0x1c);
    param_2[0xe] = *(undefined2 *)(param_1 + 0x20);
    param_2[0xf] = *(undefined2 *)(param_1 + 0x22);
    param_2[0x10] = *(undefined2 *)(param_1 + 0x24);
    param_2[0x11] = *(undefined2 *)(param_1 + 0x26);
    *(char *)(param_2 + 0x12) = param_1[0x28];
    *(char *)((int)param_2 + 0x25) = param_1[0x29];
    *(char *)(param_2 + 0x13) = param_1[0x2a];
    *(char *)((int)param_2 + 0x27) = param_1[0x2b];
    *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_1 + 0x2c);
    os_move_mem(param_2 + 0x16,param_1 + 0x30,9);
    if (*(char *)((int)param_2 + 5) == '\0') {
      if (param_1[0x33] != '\0') {
        *(undefined1 *)((int)param_2 + 0x2f) = 0xf;
      }
      uVar2 = *(uint *)(param_1 + 0x2c);
      if ((uVar2 & 0x800000) != 0) {
        *(byte *)((int)param_2 + 0x31) = *(byte *)((int)param_2 + 0x31) | 2;
        uVar2 = *(uint *)(param_1 + 0x2c);
      }
      if ((uVar2 & 0x1000000) != 0) {
        *(byte *)((int)param_2 + 0x31) = *(byte *)((int)param_2 + 0x31) | 1;
      }
      if (3 < (byte)param_1[0x30]) {
        if ((*(uint *)(param_1 + 0x2c) & 0x80000) != 0) {
          *(undefined1 *)(param_2 + 0x17) = 1;
        }
        return 0;
      }
    }
  }
  return 0;
}

