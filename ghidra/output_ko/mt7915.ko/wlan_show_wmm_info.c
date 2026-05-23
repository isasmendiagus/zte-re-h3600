// module: mt7915.ko
// function: wlan_show_wmm_info @ 0x158c94
// size: 192 bytes
//

undefined4 wlan_show_wmm_info(int param_1,uint param_2)

{
  int iVar1;
  undefined *apuStack_20 [5];
  
  apuStack_20[3] = &_LC6;
  apuStack_20[2] = &_LC5;
  apuStack_20[1] = &_LC4;
  apuStack_20[0] = &_LC3;
  if (param_1 == 0 || 3 < param_2) {
    if (-1 < DebugLevel) {
      printk("wlan_show_wmm_info para error %p, %d\n",param_1,param_2);
    }
  }
  else {
    printk("WMM type [%s]: AIFSN CWmin CWmax  TXOP(us)  ACM\n",apuStack_20[param_2]);
    iVar1 = param_1 + param_2;
    printk("                %2d   %2d   %2d    %4d       %d\n",*(undefined1 *)(iVar1 + 7),
           *(undefined1 *)(iVar1 + 0xb),*(undefined1 *)(iVar1 + 0xf),
           (uint)*(ushort *)(param_1 + param_2 * 2 + 0x14) << 5,*(undefined1 *)(iVar1 + 0x1c));
  }
  return 1;
}

