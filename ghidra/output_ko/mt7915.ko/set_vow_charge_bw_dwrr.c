// module: mt7915.ko
// function: set_vow_charge_bw_dwrr @ 0x45e10
// size: 180 bytes
//

undefined4 set_vow_charge_bw_dwrr(undefined4 param_1,char *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint local_14;
  uint local_10;
  uint local_c [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u-%u",&local_14,local_c,&local_10);
  if ((uVar1 < 2) || (0xf < local_14)) {
    uVar2 = 0;
  }
  else {
    halUmacVoWChargeBwDrrTime(local_14 & 0xff,local_c[0] & 0xff,local_10 & 0xffff);
    if (DebugLevel < 0) {
      uVar2 = 1;
    }
    else {
      if (local_c[0] == 0) {
        uVar2 = 100;
      }
      else {
        uVar2 = 0x61;
      }
      printk("%s: group%d %c charge--> %u.\n","set_vow_charge_bw_dwrr",local_14,uVar2,local_10);
      uVar2 = 1;
    }
  }
  return uVar2;
}

