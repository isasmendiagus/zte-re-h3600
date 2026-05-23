// module: mt7915.ko
// function: MATPktRxNeedConvert @ 0x79f3c
// size: 164 bytes
//

bool MATPktRxNeedConvert(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if ((((&DAT_00580e8e)[param_1] == '\x01') && (*(int *)(&DAT_0036db58 + param_1) == param_2)) &&
       ((&DAT_00580eea)[param_1] == '\0')) {
      return true;
    }
    if ((*(char *)(param_1 + 0x79463e) == '\x01') && (*(int *)(&DAT_00581308 + param_1) == param_2))
    {
      return *(char *)(param_1 + 0x79469a) == '\0';
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    return (bool)(*(byte *)(param_1 + 0xa77bcf) & 1);
  }
  return false;
}

