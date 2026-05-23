// module: plat-zxylzb_9128S.ko
// function: pon_tm_get_next_txdesc @ 0x1981c
// size: 144 bytes
//

int pon_tm_get_next_txdesc(uint param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if ((0x1ff < *(uint *)(net_txq + param_1 * 0x1c + 0x10)) &&
     (uVar3 = pon_tm_check_tx_done_nolock(param_1 & 0xff),
     0x3ff < *(uint *)(net_txq + param_1 * 0x1c + 0x10))) {
    iVar1 = param_1 * 4;
    if (uVar3 < 0x4000000) {
      *(int *)((int)&pon_tm_tx_sw_full + iVar1) = *(int *)((int)&pon_tm_tx_sw_full + iVar1) + 1;
    }
    else {
      *(int *)((int)&pon_tm_tx_full + iVar1) = *(int *)((int)&pon_tm_tx_full + iVar1) + 1;
    }
    return 0;
  }
  iVar1 = param_1 * 0x1c;
  iVar2 = *(int *)(net_txq + iVar1 + 0xc);
  uVar3 = iVar2 + 1;
  *(uint *)(net_txq + iVar1 + 0xc) = uVar3;
  if (0x3ff < uVar3) {
    *(undefined4 *)(net_txq + iVar1 + 0xc) = 0;
  }
  return *(int *)(net_txq + iVar1) + iVar2 * 0x10;
}

