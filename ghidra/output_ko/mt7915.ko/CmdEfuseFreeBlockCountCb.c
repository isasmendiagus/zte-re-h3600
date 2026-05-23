// module: mt7915.ko
// function: CmdEfuseFreeBlockCountCb @ 0x1ab4f8
// size: 112 bytes
//

void CmdEfuseFreeBlockCountCb(int param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  
  if (3 < DebugLevel) {
    printk(&_LC0,"CmdEfuseFreeBlockCountCb");
    if (3 < DebugLevel) {
      printk("ucFreeBlockNum:%d,ucTotalBlockNum:%d\n",*param_2,param_2[2]);
    }
  }
  puVar1 = *(undefined1 **)(param_1 + 0xc);
  *puVar1 = *param_2;
  puVar1[2] = param_2[2];
  return;
}

