// module: mt7915.ko
// function: APSecInit @ 0x18128
// size: 244 bytes
//

undefined4 APSecInit(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_2 + 0x174);
  if (*(int *)(param_2 + 0x2c) == 0) {
    *(undefined4 *)(param_2 + 0x2c) = 1;
  }
  if (uVar1 == 0) {
    uVar1 = 1;
    uVar2 = *(uint *)(param_2 + 0x2c) & 0x12cf8;
    *(undefined4 *)(param_2 + 0x174) = 1;
LAB_00018164:
    *(uint *)(param_2 + 0x254) = uVar1;
  }
  else {
    uVar2 = *(uint *)(param_2 + 0x2c);
    if (((uVar2 & 3) == 0) || ((uVar1 & 0xe) == 0)) {
      uVar2 = uVar2 & 0x12cf8;
      if ((uVar2 != 0) && ((uVar1 & 0x10) != 0)) {
        *(uint *)(param_2 + 0x254) = *(uint *)(param_2 + 0x254) | 0x10;
        *(undefined1 *)(param_2 + 600) = 1;
        goto LAB_00018170;
      }
      goto LAB_00018164;
    }
    uVar2 = uVar2 & 0x12cf8;
    *(uint *)(param_2 + 0x254) = uVar1;
    *(undefined1 *)(param_2 + 600) = *(undefined1 *)(param_2 + 0x178);
  }
  if (uVar2 != 0) {
    *(undefined1 *)(param_2 + 600) = 1;
  }
LAB_00018170:
  APPMFInit(param_1,param_2);
  if (*(char *)(param_2 + 0x811) == '\0') {
    *(int *)(param_2 + 0x814) = param_2 + 0x814;
    *(int *)(param_2 + 0x818) = param_2 + 0x814;
  }
  WPAMakeRSNIE(*(undefined4 *)(param_2 + 0x14),param_2 + 0x2c,0);
  return 1;
}

