// module: mt7915.ko
// function: CmdEfuseAccessReadCb @ 0x1abdd4
// size: 120 bytes
//

void CmdEfuseAccessReadCb(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  if (3 < DebugLevel) {
    printk(&_LC0,"CmdEfuseAccessReadCb");
    if (3 < DebugLevel) {
      printk("Address:%x,IsValied:%x\n",*param_2,param_2[1]);
    }
  }
  puVar1 = *(undefined4 **)(param_1 + 0xc);
  *(undefined4 *)*puVar1 = param_2[1];
  os_move_mem((void *)puVar1[1],param_2 + 2,0x10);
  return;
}

