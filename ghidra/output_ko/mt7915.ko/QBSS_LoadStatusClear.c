// module: mt7915.ko
// function: QBSS_LoadStatusClear @ 0x275e8
// size: 136 bytes
//

void QBSS_LoadStatusClear(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r2;
  
  HcGetQloadCtrl();
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    iVar1 = HcGetQloadCtrl(param_1);
    if (iVar1 == 0) {
      return;
    }
  }
  else {
    if (param_2 < 0xf) {
      uVar2 = 1;
    }
    else {
      uVar2 = 2;
    }
    iVar1 = HcGetQloadCtrlByRf(param_1,uVar2,extraout_r2,*(char *)(param_1 + 0x79504d),param_4);
    if (iVar1 == 0) {
      return;
    }
  }
  __memzero(iVar1 + 0x20,0x50);
  __memzero(iVar1 + 0x70,0x50);
  *(undefined4 *)(iVar1 + 0xc) = 0;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(undefined1 *)(iVar1 + 0xcc) = 0;
  *(undefined1 *)(iVar1 + 0xc3) = 0;
  return;
}

