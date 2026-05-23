// module: mt7915.ko
// function: mt7915_rxv_dump_start @ 0x17e110
// size: 92 bytes
//

undefined4
mt7915_rxv_dump_start(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(char *)(param_1 + 0xa7c219) != '\0') {
    *(undefined1 *)(param_1 + 0xa7c218) = 1;
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s(): dump list not alloc for start dump action.\n","mt7915_rxv_dump_start",0,DebugLevel,
         param_4);
  return 1;
}

