// module: mt7915.ko
// function: HwCtrlSetStaDWRRQuantum @ 0xaf27c
// size: 248 bytes
//

undefined4 HwCtrlSetStaDWRRQuantum(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  char *pcVar6;
  undefined1 uVar7;
  
  pcVar6 = *(char **)(param_2 + 8);
  if (2 < DebugLevel) {
    printk(&_LC4,"HwCtrlSetStaDWRRQuantum",*pcVar6,pcVar6[1]);
  }
  if (*pcVar6 == '\0') {
    *(char *)(param_1 + 0xa7a2f4) = pcVar6[1];
    *(char *)(param_1 + 0xa7a2f5) = pcVar6[1];
    *(char *)(param_1 + 0xa7a2f6) = pcVar6[1];
    *(char *)(param_1 + 0xa7a2f7) = pcVar6[1];
  }
  else {
    iVar3 = vow_watf_is_enabled(param_1);
    if (iVar3 == 0) {
      uVar7 = 6;
      uVar1 = 0xc;
      uVar4 = 0x10;
      uVar5 = 0x14;
    }
    else {
      uVar7 = *(undefined1 *)(param_1 + 0xa7a32d);
      uVar1 = *(undefined1 *)(param_1 + 0xa7a32e);
      uVar4 = *(undefined1 *)(param_1 + 0xa7a32f);
      uVar5 = *(undefined1 *)(param_1 + 0xa7a330);
    }
    *(undefined1 *)(param_1 + 0xa7a2f4) = uVar7;
    *(undefined1 *)(param_1 + 0xa7a2f5) = uVar1;
    *(undefined1 *)(param_1 + 0xa7a2f6) = uVar4;
    *(undefined1 *)(param_1 + 0xa7a2f7) = uVar5;
  }
  uVar2 = vow_set_sta(param_1,0,0x28);
  if (2 < DebugLevel) {
    printk(&_LC5,"HwCtrlSetStaDWRRQuantum",uVar2);
  }
  return 0;
}

