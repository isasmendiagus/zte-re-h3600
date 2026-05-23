// module: mt7915.ko
// function: set_vow_charge_sta_dwrr @ 0x45bb8
// size: 228 bytes
//

undefined4 set_vow_charge_sta_dwrr(int param_1,char *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  
  if (param_2 != (char *)0x0) {
    uVar1 = sscanf(param_2,"%u-%u-%u-%u",&local_18,&local_10,&local_14,&local_c);
    if (((uVar1 < 4) ||
        (uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar1 <= local_18))
       || (3 < local_14)) {
      uVar2 = 0;
    }
    else {
      halUmacVoWChargeAitTimeDRR(local_18 & 0xffff,local_14 & 0xff,local_10 & 0xff,local_c & 0xffff)
      ;
      if (DebugLevel < 0) {
        uVar2 = 1;
      }
      else {
        if (local_10 == 0) {
          uVar2 = 100;
        }
        else {
          uVar2 = 0x61;
        }
        printk("%s: sta%d/ac%d %c charge--> %u.\n","set_vow_charge_sta_dwrr",local_18,local_14,uVar2
               ,local_c);
        uVar2 = 1;
      }
    }
    return uVar2;
  }
  return 0;
}

