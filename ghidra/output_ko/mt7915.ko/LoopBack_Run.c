// module: mt7915.ko
// function: LoopBack_Run @ 0x28d508
// size: 44 bytes
//

void LoopBack_Run(undefined4 param_1,undefined4 param_2,uint param_3)

{
  if (param_3 < 0xf001) {
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, LOOPBACK length too long\n","LoopBack_Run");
  return;
}

