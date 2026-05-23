// module: mt7915.ko
// function: MSTA_IdxGet @ 0x685e8
// size: 112 bytes
//

undefined4 MSTA_IdxGet(int param_1,int param_2)

{
  if ((param_2 != 0 && param_1 != 0) && (*(char *)(param_1 + 0x794ab8) != '\0')) {
    if (*(int *)(&DAT_0036db58 + param_1) == param_2) {
      return 0;
    }
    if ((*(char *)(param_1 + 0x794ab8) != '\x01') && (*(int *)(&DAT_00581308 + param_1) == param_2))
    {
      return 1;
    }
  }
  return 0xffffffff;
}

