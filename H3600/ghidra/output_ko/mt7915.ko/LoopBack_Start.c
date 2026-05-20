// module: mt7915.ko
// function: LoopBack_Start @ 0x28ccd4
// size: 660 bytes
//

void LoopBack_Start(int param_1,uint *param_2)

{
  int iVar1;
  
  os_move_mem((void *)(param_1 + 0xa3bb18),param_2,0x2c);
  os_zero_mem(param_1 + 0xa3bb45,0xf000);
  os_zero_mem(param_1 + 0xa4ab45,0xf000);
  os_zero_mem(param_1 + 0xa3bafc,0x1c);
  if (*param_2 < 0x20) {
    if (1 < DebugLevel) {
      printk("%s startLength(0x%x) is shorter than sizeof(TMAC_TXD_L) (0x%lx)\n","LoopBack_Start",
             *param_2,0x20);
      return;
    }
    return;
  }
  OS_SPIN_LOCK(param_1 + 0xa77b58);
  *(undefined1 *)(param_1 + 0xa3bafa) = 0;
  OS_SPIN_UNLOCK(param_1 + 0xa77b58);
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa3bafc) = 0;
  *(undefined1 *)(param_1 + 0xa3baf9) = 1;
  if ((((2 < iVar1) && (printk(&_LC3,"LoopBack_Start"), 2 < DebugLevel)) &&
      (printk("IsDefaultPattern\t%d\n",param_2[3]), 2 < DebugLevel)) &&
     ((printk("RepeatTimes\t\t%u, %u\n",param_2[2],*(undefined4 *)(param_1 + 0xa3bb20)),
      2 < DebugLevel && (printk("StartLen\t\t\t%d\n",*param_2), 2 < DebugLevel)))) {
    printk("StopLen\t\t\t%d\n",param_2[1]);
  }
  *(char *)(param_1 + 0xa77b5c) = (char)param_2[3];
  if (*(char *)(param_1 + 0xa3baf8) == '\0') {
    if (*(char *)(param_1 + 0xa77ba0) == '\0') {
      iVar1 = FWSwitchToROM(param_1);
      if (iVar1 == 0) {
LAB_0028cea0:
        if (DebugLevel < 3) goto LAB_0028ce6c;
        printk("%s FWSwitchToROM\n","LoopBack_Start");
        if (*(char *)(param_1 + 0xa77ba0) != '\0') goto LAB_0028cddc;
      }
      else {
        if (-1 < DebugLevel) {
          printk("%s, Switch to ROM failed (0x%x)\n","LoopBack_Start");
          goto LAB_0028cea0;
        }
LAB_0028ce6c:
        if (*(char *)(param_1 + 0xa77ba0) != '\0') goto LAB_0028cde8;
      }
      MtCmdHIFLoopBackTest(param_1,1,1);
    }
  }
  else {
    if (DebugLevel < 3) goto LAB_0028cde8;
    printk("In LoopBack Debug Mode\n");
  }
LAB_0028cddc:
  if (2 < DebugLevel) {
    printk("***************************************%s @#@# Rx[%d]***************************************\n"
           ,"LoopBack_Start",1);
  }
LAB_0028cde8:
  iVar1 = RtmpOSTaskAttach(param_1 + 0xa77b60,LoopBack_TxThread,param_1 + 0xa77b60);
  if (iVar1 == 0) {
    return;
  }
  if (-1 < DebugLevel) {
    printk("%s, thread create fail\n","LoopBack_Start");
    return;
  }
  return;
}

