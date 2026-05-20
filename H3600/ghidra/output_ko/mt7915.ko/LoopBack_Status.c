// module: mt7915.ko
// function: LoopBack_Status @ 0x28d0c8
// size: 288 bytes
//

void LoopBack_Status(int param_1,void *param_2)

{
  os_move_mem(param_2,(void *)(param_1 + 0xa3bafc),0x1c);
  if (DebugLevel < 3) {
    return;
  }
  printk(&_LC3,"LoopBack_Status");
  if (2 < DebugLevel) {
    printk("%s, Status: %d\n","LoopBack_Status",*(undefined4 *)(param_1 + 0xa3bafc));
    if (DebugLevel < 3) {
      return;
    }
    printk("%s, FailReason: %d\n","LoopBack_Status",*(undefined4 *)(param_1 + 0xa3bb00));
    if (DebugLevel < 3) {
      return;
    }
    printk("%s, RxByteCount: %d\n","LoopBack_Status",*(undefined4 *)(param_1 + 0xa3bb10));
    if (DebugLevel < 3) {
      return;
    }
    printk("%s, RxPktCount: %d\n","LoopBack_Status",*(undefined4 *)(param_1 + 0xa3bb08));
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, TxByteCount: %d\n","LoopBack_Status",*(undefined4 *)(param_1 + 0xa3bb0c));
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, TxPktCount: %d\n","LoopBack_Status",*(undefined4 *)(param_1 + 0xa3bb04));
  return;
}

