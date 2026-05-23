// module: mt7915.ko
// function: WfHifInit @ 0xb296c
// size: 188 bytes
//

int WfHifInit(int param_1)

{
  int iVar1;
  undefined1 auStack_12 [6];
  
  os_zero_mem(auStack_12,2);
  iVar1 = WfHifSysInit(param_1,auStack_12);
  if (iVar1 == 0) {
    hif_sys_init(*(undefined4 *)(param_1 + 0xa797a0));
    mt_wlan_hook_call(0,param_1,0);
    if (2 < DebugLevel) {
      printk("<--%s(), Success!\n","WfHifInit");
    }
  }
  else {
    WfHifSysExit(param_1);
    if (2 < DebugLevel) {
      printk("<--%s(), Err! status=%d\n","WfHifInit",iVar1);
    }
  }
  return iVar1;
}

