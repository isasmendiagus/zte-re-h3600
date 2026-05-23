// module: mt7915.ko
// function: set_vow_max_ratio @ 0x45088
// size: 276 bytes
//

undefined4 set_vow_max_ratio(int param_1,char *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  uint local_18;
  undefined4 local_14;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar2 = sscanf(param_2,"%u-%u",&local_18,&local_14);
  if ((1 < uVar2) && (local_18 < 0x10)) {
    iVar3 = param_1 + local_18 * 0x1c;
    *(char *)(iVar3 + 0xa7982d) = (char)local_14;
    uVar1 = vow_convert_airtime_token(param_1,1,local_18 & 0xff);
    *(undefined2 *)(iVar3 + 0xa7983e) = uVar1;
    vow_set_group(param_1,local_18 & 0xff,7);
    iVar3 = vow_set_at_estimator_group(param_1,3,local_18 & 0xff);
    if (DebugLevel < 0) {
      if (iVar3 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: group %d set %u.\n","set_vow_max_ratio",local_18,local_14);
      if (iVar3 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_max_ratio");
      }
    }
  }
  return 0;
}

