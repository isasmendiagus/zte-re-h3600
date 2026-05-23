// module: mt7915.ko
// function: SetCommonHtVht @ 0x14a858
// size: 100 bytes
//

undefined4 SetCommonHtVht(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): Can\'t update HT/VHT due to wdev is null!\n","SetCommonHtVht",param_3,DebugLevel
             ,param_4);
    }
  }
  else {
    SetCommonHT();
    if ((*(ushort *)(param_2 + 0x18) & 0x20) != 0) {
      SetCommonVHT(param_1,param_2);
      return 1;
    }
  }
  return 1;
}

