// module: mt7915.ko
// function: LoopBack_RawData @ 0x28d1ec
// size: 296 bytes
//

void LoopBack_RawData(int param_1,uint *param_2,int param_3,void *param_4)

{
  size_t sVar1;
  
  if ((0xf000 < *param_2) && (*param_2 = 0xf000, 2 < DebugLevel)) {
    printk("%s, max length is %d\n","LoopBack_RawData");
  }
  if (param_3 == 0) {
    sVar1 = *(size_t *)(param_1 + 0xa59b4c);
    *param_2 = sVar1;
    os_move_mem(param_4,(void *)(param_1 + 0xa4ab45),sVar1);
  }
  else {
    sVar1 = *(size_t *)(param_1 + 0xa59b48);
    *param_2 = sVar1;
    os_move_mem(param_4,(void *)(param_1 + 0xa3bb45),sVar1);
  }
  if (((2 < DebugLevel) &&
      (printk("%s, Length = 0x%x\n","LoopBack_RawData",*param_2), 2 < DebugLevel)) &&
     (printk("%s, LoopBackRxRawLen = 0x%x\n","LoopBack_RawData",*(undefined4 *)(param_1 + 0xa59b4c))
     , 2 < DebugLevel)) {
    printk("%s, LoopBackTxRawLen = 0x%x\n","LoopBack_RawData",*(undefined4 *)(param_1 + 0xa59b48));
    return;
  }
  return;
}

