// module: mt7915.ko
// function: set_vow_sta_dwrr_quantum_id @ 0x44a98
// size: 280 bytes
//

undefined4 set_vow_sta_dwrr_quantum_id(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  uint local_1c;
  uint local_18;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u-%u",&local_18,local_14,&local_1c);
  if ((((2 < uVar1) &&
       (uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), local_18 < uVar1)) &&
      (local_14[0] < 4)) && (local_1c < 8)) {
    *(char *)(param_1 + local_18 * 8 + local_14[0] + 0xa799e8) = (char)local_1c;
    iVar2 = vow_set_sta(param_1,local_18 & 0xffff,local_14[0] + 3);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set sta %d, ac %d, quantum id %u.\n","set_vow_sta_dwrr_quantum_id",local_18,
             local_14[0],local_1c);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_sta_dwrr_quantum_id");
      }
    }
  }
  return 0;
}

