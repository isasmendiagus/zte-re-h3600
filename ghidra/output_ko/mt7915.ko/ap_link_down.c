// module: mt7915.ko
// function: ap_link_down @ 0x16c3c
// size: 148 bytes
//

undefined4 ap_link_down(int param_1)

{
  int iVar1;
  
  APStopRekeyTimer(*(undefined4 *)(param_1 + 8),param_1);
  if (1 < *(uint *)(param_1 + 0x990)) {
    *(undefined4 *)(param_1 + 0x990) = 2;
    MbssKickOutStas(*(undefined4 *)(param_1 + 8),*(undefined1 *)(param_1 + 0xe),4);
    UpdateBeaconHandler(*(undefined4 *)(param_1 + 8),param_1,6);
    iVar1 = wifi_sys_linkdown(param_1);
    if (iVar1 != 1) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s(): linkdown fail!\n","ap_link_down");
      return 0;
    }
  }
  return 1;
}

