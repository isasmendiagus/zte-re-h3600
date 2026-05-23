// module: mt7915.ko
// function: set_fw_dbg @ 0xbbe58
// size: 532 bytes
//

undefined4 set_fw_dbg(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *local_14;
  
  local_14 = param_2;
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    pcVar2 = strsep(&local_14,":");
    uVar1 = os_str_toul(pcVar2,0,10);
    if ((local_14 == (char *)0x0) || (*local_14 == '\0')) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = os_str_toul(local_14,0,10);
    }
    if (0 < DebugLevel) {
      printk("%s: set fw debug level to 0x%x for module index 0x%x\n","set_fw_dbg",uVar1,uVar3);
    }
    MtCmdFwDbgCtrl(param_1,uVar1,uVar3);
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("Usage: fw_dbg=[debug level bitmap]:[debug module index]\n");
  if (DebugLevel < 1) {
LAB_000bbf8c:
    if (0 < DebugLevel) {
      printk("\t\t DBG_CLASS_INFO  (1 << 3)\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t DBG_CLASS_LOUD  (1 << 4)\n");
      goto LAB_000bbfc4;
    }
  }
  else {
    printk("\tdebug level bitmap:\n");
    if (DebugLevel < 1) {
      return 0;
    }
    printk("\t\t DBG_CLASS_ERROR (1 << 0)\n");
    if (0 < DebugLevel) {
      printk("\t\t DBG_CLASS_WARN  (1 << 1)\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t DBG_CLASS_STATE (1 << 2)\n");
      goto LAB_000bbf8c;
    }
LAB_000bbfc4:
    if (DebugLevel < 1) goto LAB_000bc034;
    printk("\tdebug module index:\n");
    if (DebugLevel < 1) {
      return 0;
    }
    printk("\t\t If not specified, means all modules.\n");
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("Example:\n");
  if (DebugLevel < 1) {
    return 0;
  }
  printk("\t iwpriv ra0 set fw_dbg=3 (turn on ERROR and WARN for all modules\n");
LAB_000bc034:
  if (0 < DebugLevel) {
    printk("\t iwpriv ra0 set fw_dbg=1:0 (turn on ERROR for module 0\n");
  }
  return 0;
}

