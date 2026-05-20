// module: mt7915.ko
// function: MtReadPwrLimitTable @ 0x150f94
// size: 220 bytes
//

undefined4 MtReadPwrLimitTable(int param_1,void *param_2,int param_3,undefined4 param_4)

{
  if (param_2 == (void *)0x0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: null pointer for buffer to read power limit table !!\n","MtReadPwrLimitTable",
           param_3,DebugLevel,param_4);
    return 1;
  }
  if (0 < DebugLevel) {
    printk(&_LC6,"MtReadPwrLimitTable",*(undefined1 *)(param_1 + 0x794eac),param_1 + 0x794000,
           param_4);
  }
  os_zero_mem(param_2,42000);
  if (param_3 != 0) {
    if (param_3 != 1) {
      return 0;
    }
    os_move_mem(param_2,Backoff_01,0x8f9e);
    return 0;
  }
  os_move_mem(param_2,sku,42000);
  return 0;
}

