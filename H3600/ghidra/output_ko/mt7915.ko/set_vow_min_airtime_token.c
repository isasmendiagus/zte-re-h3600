// module: mt7915.ko
// function: set_vow_min_airtime_token @ 0x4348c
// size: 228 bytes
//

undefined4 set_vow_min_airtime_token(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  uint local_18;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",&local_18,local_14);
  if ((1 < uVar1) && (local_18 < 0x10)) {
    *(short *)(param_1 + local_18 * 0x1c + 0xa7983c) = (short)local_14[0];
    iVar2 = vow_set_group(param_1,local_18 & 0xff,4);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: group %d set %u.\n","set_vow_min_airtime_token",local_18,local_14[0]);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_min_airtime_token");
      }
    }
  }
  return 0;
}

