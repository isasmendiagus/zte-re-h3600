// module: mt7915.ko
// function: set_vow_sta_dwrr_quantum @ 0x4452c
// size: 228 bytes
//

undefined4 set_vow_sta_dwrr_quantum(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 local_18;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",local_14,&local_18);
  if ((1 < uVar1) && (local_14[0] < 8)) {
    *(char *)(param_1 + local_14[0] + 0xa7a2f4) = (char)local_18;
    iVar2 = vow_set_sta(param_1,0,local_14[0] + 0x20);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set quantum id %u, val %u.\n","set_vow_sta_dwrr_quantum",local_14[0],local_18);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_sta_dwrr_quantum");
      }
    }
  }
  return 0;
}

