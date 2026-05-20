// module: mt7915.ko
// function: set_vow_show_en @ 0x46280
// size: 136 bytes
//

undefined4 set_vow_show_en(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",&local_c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    bVar3 = DebugLevel < 0;
    *(char *)(param_1 + 0xa7a31b) = (char)local_c;
    if (bVar3) {
      uVar2 = 1;
    }
    else {
      printk("%s: DVT Show enable %d.\n","set_vow_show_en",local_c & 0xff);
      uVar2 = 1;
    }
  }
  return uVar2;
}

