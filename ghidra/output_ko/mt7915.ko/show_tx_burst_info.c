// module: mt7915.ko
// function: show_tx_burst_info @ 0xe1164
// size: 396 bytes
//

undefined4 show_tx_burst_info(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  int *piVar3;
  int iVar4;
  char cVar5;
  
  if (0 < DebugLevel) {
    printk("[%s]\n","dump_tx_burst_info",param_3,DebugLevel,param_4);
    param_3 = extraout_r2_01;
  }
  piVar3 = (int *)(param_1 + 8);
  cVar5 = -1;
  iVar4 = 0;
  do {
    piVar3 = piVar3 + 1;
    iVar2 = *piVar3;
    if (iVar2 == 0) {
      return 1;
    }
    if (*(char *)(iVar2 + 0x999) != cVar5) {
      iVar2 = HcGetEdca(param_1);
      if (iVar2 == 0) {
        return 1;
      }
      uVar1 = HcGetWmmIdx(param_1,*piVar3);
      if ((((0 < DebugLevel) &&
           (printk("<bss_%x>\n",*(undefined1 *)(*piVar3 + 0x999)), 0 < DebugLevel)) &&
          (printk(" |-[wmm_idx]: %x\n",uVar1), 0 < DebugLevel)) &&
         (printk(" |-[bitmap]: %08x\n",*(undefined4 *)(*piVar3 + 0x9b0)), 0 < DebugLevel)) {
        printk(" |-[prio:level]:");
      }
      FUN_000d7f70(*piVar3 + 0x9b4);
      iVar2 = *piVar3;
      cVar5 = *(char *)(iVar2 + 0x999);
      param_3 = extraout_r2;
    }
    if (0 < DebugLevel) {
      printk(" |---<wdev_%x>\n",iVar4,param_3,DebugLevel,param_4);
      if ((0 < DebugLevel) &&
         (printk("      |-[bitmap]: %08x\n",*(undefined4 *)(*piVar3 + 0x8e0)), 0 < DebugLevel)) {
        printk("      |-[prio:level]:");
      }
      iVar2 = *piVar3;
    }
    iVar4 = iVar4 + 1;
    FUN_000d7f70(iVar2 + 0x8e4);
    param_3 = extraout_r2_00;
  } while (iVar4 != 0x68);
  return 1;
}

