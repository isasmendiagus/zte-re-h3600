// module: mt7915.ko
// function: ap_inf_close @ 0x16f80
// size: 204 bytes
//

undefined4 ap_inf_close(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *(int *)(param_1 + 8);
  if (iVar2 == 0) {
    return 0;
  }
  if (*(char *)(iVar2 + 0x286285) == '\x01') {
    *(undefined1 *)(param_1 + 0xb1c) = 0;
    iVar1 = wdev_do_linkdown();
    if ((iVar1 != 1) && (2 < DebugLevel)) {
      printk("%s() linkdown fail!!!\n","ap_inf_close");
    }
    iVar1 = wifi_sys_close(param_1);
    if (iVar1 == 1) {
      auto_ch_select_reset_sm(iVar2,param_1);
      uVar3 = 1;
    }
    else {
      if (DebugLevel < 3) {
        return 0;
      }
      uVar3 = 0;
      printk("%s() close fail!!!\n","ap_inf_close");
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

