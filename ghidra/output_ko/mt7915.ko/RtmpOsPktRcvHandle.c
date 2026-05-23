// module: mt7915.ko
// function: RtmpOsPktRcvHandle @ 0x244cd8
// size: 208 bytes
//

void RtmpOsPktRcvHandle(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 local_10;
  
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x18) + 0x4c4) + 0x4058);
  local_10 = param_4;
  if (((iVar2 != 0) && ((*(uint *)(*(int *)(iVar2 + 0x10) + 0x30) & 1) != 0)) &&
     (iVar2 = idm_fdb_recv_handle(iVar2,param_1), iVar2 == 0)) {
    wlan_dbg_radio_statistics_inc(0,0x11);
    return;
  }
  iVar2 = ffe_receive_skb_locked(param_1,3);
  if (iVar2 == 0) {
    return;
  }
  uVar1 = eth_type_trans(param_1,*(undefined4 *)(param_1 + 0x18));
  *(undefined2 *)(param_1 + 0xa4) = uVar1;
  if ((param_2 == 0) || ((*(uint *)(((uint)&local_10 & 0xffffe000) + 4) & 0x100) == 0)) {
    netif_rx(param_1);
  }
  else {
    napi_gro_receive(param_2,param_1);
  }
  wlan_dbg_radio_statistics_inc(0,0x12);
  return;
}

