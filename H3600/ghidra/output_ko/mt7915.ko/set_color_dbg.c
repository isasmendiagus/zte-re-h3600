// module: mt7915.ko
// function: set_color_dbg @ 0xdaef4
// size: 264 bytes
//

undefined4 set_color_dbg(undefined4 param_1,char *param_2)

{
  int iVar1;
  uint local_14;
  uint local_10;
  undefined1 local_c [4];
  
  if (((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
     (iVar1 = sscanf(param_2,"%u:%u:%u",&local_14,&local_10,local_c), iVar1 != 3)) {
    printk("iwpriv ra0 set color_dbg=[wdev_idx]:[action]:[value]\n");
    printk("[action] 1:occupy, 2:setperiod, 3:trigger, 4: change\n");
    printk("         5:assign manually 6: change manually\n");
  }
  else if (local_14 < 0x68) {
    if (local_10 < 7) {
      set_bss_color_dbg(param_1,local_14 & 0xff,local_10 & 0xff,local_c[0]);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("action is out of range\n");
    }
  }
  else if (-1 < DebugLevel) {
    printk("wdev_index is out of range\n");
  }
  return 0;
}

