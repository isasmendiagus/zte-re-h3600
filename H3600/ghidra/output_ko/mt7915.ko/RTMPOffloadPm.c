// module: mt7915.ko
// function: RTMPOffloadPm @ 0x12944c
// size: 632 bytes
//

void RTMPOffloadPm(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    printk(&_LC14,0x2c8);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk("%s--->wcid(%d), ucPmNumber(%d), ucPmState(%d)\n","RTMPOffloadPm",
           *(undefined2 *)(param_2 + 0x2124be),param_3,param_4);
  }
  if (param_3 == 4) {
    LowPowerDebug(param_1,param_2);
    iVar1 = DebugLevel;
    if (*(char *)(param_2 + 0x2124c0) == '\0') {
      if (param_4 == 1) {
        if (DebugLevel < 3) {
          *(undefined2 *)(param_2 + 0x2124b8) = 1;
        }
        else {
          printk("%s(line=%d): -->\n","RTMPOffloadPm",0x2d5);
          iVar1 = DebugLevel;
          *(undefined2 *)(param_2 + 0x2124b8) = 1;
          if (2 < iVar1) {
            printk("MlmeSetPsmBit = %d\n",1);
            iVar1 = DebugLevel;
          }
        }
        if (0 < iVar1) {
          printk("%s::***** H/W Enter PM4 *****\n","RTMPOffloadPm");
        }
        AsicExtPmStateCtrl(param_1,param_2,4,1);
        iVar1 = DebugLevel;
        *(undefined1 *)(param_2 + 0x2124c0) = 1;
        goto LAB_00129554;
      }
    }
    else if (param_4 == 2) {
      if (DebugLevel < 3) {
        *(undefined2 *)(param_2 + 0x2124b8) = 0;
      }
      else {
        printk("%s(line=%d): -->\n","RTMPOffloadPm",0x2dc);
        iVar1 = DebugLevel;
        *(undefined2 *)(param_2 + 0x2124b8) = 0;
        if (2 < iVar1) {
          printk("MlmeSetPsmBit = %d\n");
          iVar1 = DebugLevel;
        }
      }
      if (0 < iVar1) {
        printk("%s::***** H/W Exit PM4 *****\n","RTMPOffloadPm");
      }
      *(undefined4 *)(param_2 + 0x21245c) = jiffies;
      AsicExtPmStateCtrl(param_1,param_2,4,2);
      iVar1 = DebugLevel;
      *(undefined1 *)(param_2 + 0x2124c0) = 0;
      goto LAB_00129554;
    }
    if (DebugLevel < 3) {
      return;
    }
    printk("%s::***** No Need to handle this. *****\n","RTMPOffloadPm");
    iVar1 = DebugLevel;
  }
  else {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s:: Unknown PM mode, ERROR!\n","RTMPOffloadPm");
    iVar1 = DebugLevel;
  }
LAB_00129554:
  if (iVar1 < 3) {
    return;
  }
  printk("%s<---\n","RTMPOffloadPm");
  return;
}

