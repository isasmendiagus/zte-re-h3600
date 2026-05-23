// module: mt7915.ko
// function: RTMPCheckPhyMode @ 0x139f78
// size: 292 bytes
//

undefined4 RTMPCheckPhyMode(undefined4 param_1,int param_2,byte *param_3)

{
  if (param_2 == 1) {
    if ((*param_3 & 0xb1) != 0) {
      if (2 < DebugLevel) {
        printk("%s(): Warning! The board type is 2.4G only!\n","RTMPCheckPhyMode");
      }
      *param_3 = 9;
LAB_00139fe4:
      if (2 < DebugLevel) {
        printk("%s(): Changed PhyMode to %u\n","RTMPCheckPhyMode",*param_3);
        return 0;
      }
      return 0;
    }
  }
  else if (param_2 == 2) {
    if ((*param_3 & 0x4e) != 0) {
      if (2 < DebugLevel) {
        printk("%s(): Warning! The board type is 5G only!\n","RTMPCheckPhyMode");
      }
      *param_3 = 8;
      goto LAB_00139fe4;
    }
  }
  else if ((param_2 != 3) && (2 < DebugLevel)) {
    printk("%s(): Unknown supported band (%u), assume dual band used.\n","RTMPCheckPhyMode",param_2)
    ;
  }
  return 1;
}

