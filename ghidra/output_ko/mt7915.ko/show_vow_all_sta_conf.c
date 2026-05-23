// module: mt7915.ko
// function: show_vow_all_sta_conf @ 0x47284
// size: 100 bytes
//

undefined4 show_vow_all_sta_conf(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char acStack_14 [4];
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 0) {
    iVar2 = 0;
    do {
      iVar3 = iVar2 + 1;
      snprintf(acStack_14,4,"%d",iVar2);
      show_vow_sta_conf(param_1,acStack_14);
      iVar2 = iVar3;
    } while (iVar3 != iVar1);
  }
  return 1;
}

