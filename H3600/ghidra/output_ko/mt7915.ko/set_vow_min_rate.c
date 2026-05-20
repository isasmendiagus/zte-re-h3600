// module: mt7915.ko
// function: set_vow_min_rate @ 0x44d68
// size: 252 bytes
//

undefined4 set_vow_min_rate(int param_1,char *param_2)

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
    *(short *)(iVar3 + 0xa79828) = (short)local_14;
    uVar1 = vow_convert_rate_token(param_1,0,local_18 & 0xff);
    *(undefined2 *)(iVar3 + 0xa79838) = uVar1;
    iVar3 = vow_set_group(param_1,local_18 & 0xff,1);
    if (DebugLevel < 0) {
      if (iVar3 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: group %d set rate %u\n","set_vow_min_rate",local_18,local_14);
      if (iVar3 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_min_rate");
      }
    }
  }
  return 0;
}

