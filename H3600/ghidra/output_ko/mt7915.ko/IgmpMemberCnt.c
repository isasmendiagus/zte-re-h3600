// module: mt7915.ko
// function: IgmpMemberCnt @ 0x241318
// size: 68 bytes
//

undefined1 IgmpMemberCnt(int param_1)

{
  if (param_1 != 0) {
    return *(undefined1 *)(param_1 + 8);
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s: membert list doesn\'t exist.\n","IgmpMemberCnt");
  return 0;
}

