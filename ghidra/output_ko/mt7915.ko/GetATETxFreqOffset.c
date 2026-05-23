// module: mt7915.ko
// function: GetATETxFreqOffset @ 0x261c1c
// size: 64 bytes
//

undefined4 GetATETxFreqOffset(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (0 < DebugLevel) {
    printk("%s: FreqOffset = %d\n","GetATETxFreqOffset",*(undefined4 *)(param_1 + 0xa7bf44),
           DebugLevel,param_4);
  }
  return 1;
}

