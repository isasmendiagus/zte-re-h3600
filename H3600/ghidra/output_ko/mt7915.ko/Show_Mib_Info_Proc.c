// module: mt7915.ko
// function: Show_Mib_Info_Proc @ 0xe0660
// size: 672 bytes
//

undefined4 Show_Mib_Info_Proc(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)((int)param_1 + 0x286285) != '\x01') {
    return 1;
  }
  if (0 < DebugLevel) {
    printk("show mib info statistic:\n");
  }
  iVar2 = *param_1;
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("pObj is NULL\n");
      return 0;
    }
    return 0;
  }
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("invalid input, should be enable of disable show mib\n");
    return 1;
  }
  cVar1 = os_str_tol(param_2,0,10);
  *(char *)(param_1 + 0x29f0f6) = cVar1;
  if (cVar1 != '\x01') {
    return 1;
  }
  iVar2 = HcGetBandByWdev(param_1 + *(int *)(iVar2 + 0x3c) * 0x160d + 0xadc92);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%s RX FCS Error Count         = %d\n","Show_Mib_Info_Proc",
         param_1[iVar2 * 0x42 + 0x28e72e]);
  if (0 < DebugLevel) {
    printk("%s RX FIFO Overflow Count     = %d\n","Show_Mib_Info_Proc",
           param_1[iVar2 * 0x42 + 0x28e730]);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s RX MPDU Count              = %ld\n","Show_Mib_Info_Proc",
           param_1[iVar2 * 0x42 + 0x28e732]);
    if (DebugLevel < 1) goto LAB_000e0850;
    printk("%s Channel Idle Count         = %ld\n","Show_Mib_Info_Proc",
           param_1[iVar2 * 0x42 + 0x28e734]);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s CCA NAV TX Time            = %ld\n","Show_Mib_Info_Proc",
           param_1[iVar2 * 0x42 + 0x28e736]);
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%s RX MDRDY Count             = %ld\n","Show_Mib_Info_Proc",
         param_1[iVar2 * 0x42 + 0x28e738]);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%s S CCA Time                 = %ld\n","Show_Mib_Info_Proc",
         param_1[iVar2 * 0x42 + 0x28e73a]);
LAB_000e0850:
  if (0 < DebugLevel) {
    printk("%s P ED Time                  = %ld\n","Show_Mib_Info_Proc",
           param_1[iVar2 * 0x42 + 0x28e73c]);
    if (0 < DebugLevel) {
      printk("%s RX Total Byte Count        = %ld\n","Show_Mib_Info_Proc",
             param_1[iVar2 * 0x42 + 0x28e73e]);
    }
  }
  return 1;
}

