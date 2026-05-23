// module: mt7915.ko
// function: MtCmdGetFreqOffsetRsp @ 0x1ac78c
// size: 68 bytes
//

void MtCmdGetFreqOffsetRsp(int param_1,int param_2)

{
  os_move_mem(*(void **)(param_1 + 0xc),(void *)(param_2 + 4),4);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, FreqOffset:%d\n","MtCmdGetFreqOffsetRsp",*(undefined4 *)(param_2 + 4));
  return;
}

