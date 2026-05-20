// module: mt7915.ko
// function: mt_op_set_mu_count @ 0x258e2c
// size: 104 bytes
//

int mt_op_set_mu_count(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_18 [4];
  int local_14;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    iVar2 = 0x503;
  }
  else {
    iVar2 = net_ad_get_band_idx(param_2,auStack_18);
    if (iVar2 == 0) {
      if (param_3 == -0x70000001) {
        param_3 = 0;
      }
      local_14 = param_3;
      iVar1 = set_muru_mu_tx_pkt_cnt(iVar1,auStack_18);
      if (iVar1 == 0) {
        iVar2 = 0x501;
      }
    }
  }
  return iVar2;
}

