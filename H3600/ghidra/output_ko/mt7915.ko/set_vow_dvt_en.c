// module: mt7915.ko
// function: set_vow_dvt_en @ 0x48ea0
// size: 176 bytes
//

undefined4 set_vow_dvt_en(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",&local_c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (local_c == 0) {
      vow_reset(param_1);
      vow_variable_reset(param_1);
      vow_init(param_1);
    }
    iVar1 = DebugLevel;
    *(char *)(param_1 + 0xa7a31a) = (char)local_c;
    if (iVar1 < 0) {
      uVar2 = 1;
    }
    else {
      printk("%s: DVT enable %d.\n","set_vow_dvt_en",local_c & 0xff);
      uVar2 = 1;
    }
  }
  return uVar2;
}

