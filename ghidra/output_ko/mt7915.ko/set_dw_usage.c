// module: mt7915.ko
// function: set_dw_usage @ 0x99bcc
// size: 240 bytes
//

void set_dw_usage(int param_1)

{
  if (0 < DebugLevel) {
    printk("usage:\n\n");
    if (param_1 == 0) {
      if (0 < DebugLevel) {
        printk("\tiwpriv ra0 set txcmd_sxn_dw=%s%s%s%s%s%s\n","[SXN#]-","[DW#]-","[START_BIT]-",
               "[BIT_NUM]-","[VALUE]-","[DL_UL_IDX]");
      }
    }
    else if (0 < DebugLevel) {
      printk("\tiwpriv ra0 set txcmd_sxn_user_dw=%s%s%s%s%s%s%s\n","[SXN#]-","[USER_INDEX]-",
             "[DW#]-","[START_BIT]-","[BIT_NUM]-","[VALUE]-","[DL_UL_IDX]");
    }
  }
  return;
}

