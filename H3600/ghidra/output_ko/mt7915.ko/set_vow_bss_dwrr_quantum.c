// module: mt7915.ko
// function: set_vow_bss_dwrr_quantum @ 0x44bb4
// size: 232 bytes
//

undefined4 set_vow_bss_dwrr_quantum(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 local_18;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",local_14,&local_18);
  if ((1 < uVar1) && (local_14[0] < 0x10)) {
    *(char *)(param_1 + local_14[0] * 0x1c + 0xa79837) = (char)local_18;
    iVar2 = vow_set_group(param_1,local_14[0] & 0xff,local_14[0] + 0x20);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set group %d, quantum id %u.\n","set_vow_bss_dwrr_quantum",local_14[0],local_18);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_bss_dwrr_quantum");
      }
    }
  }
  return 0;
}

