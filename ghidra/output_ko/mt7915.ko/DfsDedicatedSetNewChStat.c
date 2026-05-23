// module: mt7915.ko
// function: DfsDedicatedSetNewChStat @ 0x2349d8
// size: 76 bytes
//

void DfsDedicatedSetNewChStat(int param_1,int param_2)

{
  if ((*(ushort *)(param_2 + 0x18) & 0xb1) == 0) {
    return;
  }
  if (*(char *)(param_1 + 0x795404) == '\0') {
    return;
  }
  *(undefined4 *)(param_1 + 0x79540c) = 0;
  if (DebugLevel < 1) {
    return;
  }
  printk("%s() set to DFS channel - initialize stat\n","DfsDedicatedSetNewChStat");
  return;
}

