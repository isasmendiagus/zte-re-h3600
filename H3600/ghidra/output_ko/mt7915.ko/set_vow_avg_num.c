// module: mt7915.ko
// function: set_vow_avg_num @ 0x461e4
// size: 152 bytes
//

undefined4 set_vow_avg_num(int param_1,char *param_2)

{
  int iVar1;
  bool bVar2;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",&local_c);
  if ((iVar1 != 0) && (local_c < 1000)) {
    bVar2 = -1 < DebugLevel;
    *(short *)(param_1 + 0xa7a320) = (short)local_c;
    if (bVar2) {
      printk("%s: average numer %d.\n","set_vow_avg_num");
    }
    return 1;
  }
  return 0;
}

