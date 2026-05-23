// module: mt7915.ko
// function: CmdMultipleMacRegAccessWriteCb @ 0x1ac564
// size: 48 bytes
//

void CmdMultipleMacRegAccessWriteCb(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x14) == 0) {
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: fail\n","CmdMultipleMacRegAccessWriteCb");
  return;
}

