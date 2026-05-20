// module: mt7915.ko
// function: mt_op_trigger_mu_counting @ 0x258e94
// size: 120 bytes
//

int mt_op_trigger_mu_counting(int param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 uStack_18;
  undefined1 local_17;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    iVar2 = 0x503;
  }
  else {
    sys_ad_zero_mem(&uStack_18,8);
    iVar2 = net_ad_get_band_idx(param_2,&uStack_18);
    if (iVar2 == 0) {
      local_17 = param_3;
      iVar2 = set_muru_mu_tx_pkt_en(iVar1,&uStack_18);
      iVar1 = 0;
      if (iVar2 == 0) {
        iVar1 = 0x501;
      }
      return iVar1;
    }
  }
  return iVar2;
}

