// module: mt7915.ko
// function: vow_init_sta @ 0x4259c
// size: 176 bytes
//

void vow_init_sta(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(param_1 + 0xa7a2ea) == '\0') {
    *(undefined1 *)(param_1 + 0xa7a2f2) = 1;
  }
  vow_set_sta_DWRR_max_time(param_1);
  uVar2 = *(uint *)(param_1 + 0xa7a2e8) & 0xff00ff;
  if (uVar2 != 0) {
    vow_set_sta(param_1,0,0x28,uVar2,param_4);
    if (uVar1 != 0) {
      uVar3 = 0;
      uVar2 = 0;
      do {
        uVar3 = uVar3 + 1;
        vow_set_sta(param_1,uVar2,0);
        vow_set_sta(param_1,uVar2,1);
        vow_set_sta(param_1,uVar2,0x30);
        uVar2 = uVar3 & 0xffff;
      } while ((uVar3 & 0xffff) < uVar1);
      return;
    }
    return;
  }
  return;
}

