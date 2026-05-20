// module: mt7915.ko
// function: IgmpPktInfoQuery @ 0x2425f8
// size: 220 bytes
//

undefined4
IgmpPktInfoQuery(int param_1,byte *param_2,undefined4 param_3,undefined4 *param_4,
                undefined4 *param_5,int *param_6)

{
  int iVar1;
  undefined4 *extraout_r2;
  undefined4 *puVar2;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  byte local_13;
  byte local_12;
  byte local_11;
  
  if ((*param_2 & 1) == 0) {
    return 0;
  }
  if (*param_2 == 0xff) {
    if (param_2 != (byte *)0xffffffe2) {
      local_12 = param_2[0x20];
      local_11 = param_2[0x21];
      local_13 = param_2[0x1f] & 0x7f;
      local_16 = 1;
      local_15 = 0;
      local_14 = 0x5e;
    }
    iVar1 = MulticastFilterTableLookup(*(undefined4 *)(param_1 + 0xa77bc4),&local_16,*param_4);
    puVar2 = extraout_r2;
    if (iVar1 != 0) {
      puVar2 = param_5;
    }
    *param_6 = iVar1;
    if (iVar1 != 0) {
      *puVar2 = 2;
    }
    return 0;
  }
  if (*(short *)(param_2 + 0xc) == -0x227a) {
    IPv6MulticastFilterExcluded(param_2,param_2 + 0xc);
  }
  *param_6 = 0;
  *param_5 = 3;
  return 0;
}

