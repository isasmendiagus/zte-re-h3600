// module: mt7915.ko
// function: CmdAccessRegReadCb @ 0x1c2994
// size: 88 bytes
//

void CmdAccessRegReadCb(int param_1,int param_2,int param_3)

{
  if (3 < DebugLevel) {
    printk(&_LC14,"CmdAccessRegReadCb");
  }
  os_move_mem(*(void **)(param_1 + 0xc),(void *)(param_2 + 4),param_3 - 4);
  return;
}

