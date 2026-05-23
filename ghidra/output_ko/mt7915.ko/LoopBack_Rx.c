// module: mt7915.ko
// function: LoopBack_Rx @ 0x28dc18
// size: 424 bytes
//

void LoopBack_Rx(int param_1,size_t param_2,void *param_3)

{
  size_t __n;
  ushort local_2c [6];
  
  if ((*(uint *)(param_1 + 0xa3baf8) & 0xffff00) == 0) {
    return;
  }
  if (*(char *)(param_1 + 0xa3baf8) == '\0') {
    if (2 < DebugLevel) {
      printk("Driver Rx LoopBackRunning\n");
    }
    os_move_mem(local_2c,param_3,0xc);
    __n = (size_t)local_2c[0];
    if (0xf000 < __n) {
      if (DebugLevel < 3) {
        __n = 0xf000;
        goto LAB_0028dc6c;
      }
      printk("%s, max length is %d\n","LoopBack_Rx",0xf000);
      __n = 0xf000;
    }
  }
  else {
    __n = param_2;
    if (DebugLevel < 3) goto LAB_0028dc6c;
    printk("%s, Debug Mode, Total Len:%d\n","LoopBack_Rx",param_2);
  }
  if (2 < DebugLevel) {
    printk("%s, Total Length = %d, LPLength is %d, bytecount = %d\n","LoopBack_Rx",param_2,__n,
           local_2c[0]);
  }
LAB_0028dc6c:
  *(size_t *)(param_1 + 0xa3bb10) = __n + *(int *)(param_1 + 0xa3bb10);
  *(int *)(param_1 + 0xa3bb08) = *(int *)(param_1 + 0xa3bb08) + 1;
  os_move_mem((void *)(param_1 + 0xa4ab45),param_3,__n);
  *(size_t *)(param_1 + 0xa59b4c) = __n;
  if (*(char *)(param_1 + 0xa77ba0) == '\0') {
    LoopBack_BitTrueCheck(param_1);
  }
  OS_SPIN_LOCK(param_1 + 0xa77b58);
  *(undefined1 *)(param_1 + 0xa3bafa) = 0;
  OS_SPIN_UNLOCK(param_1 + 0xa77b58);
  if (2 < DebugLevel) {
    printk("%s, RxPktCount = %d\n","LoopBack_Rx",*(undefined4 *)(param_1 + 0xa3bb08));
  }
  return;
}

