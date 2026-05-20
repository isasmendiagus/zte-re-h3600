// module: mt7915.ko
// function: ht_oper_init @ 0x107e24
// size: 144 bytes
//

void ht_oper_init(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  param_2[1] = 0;
  *param_2 = 0;
  uVar1 = wlan_config_get_ht_ldpc();
  param_2[3] = uVar1;
  uVar1 = wlan_config_get_ht_stbc(param_1);
  param_2[2] = uVar1;
  uVar1 = wlan_config_get_ht_gi(param_1);
  param_2[4] = uVar1;
  uVar2 = wlan_config_get_frag_thld(param_1);
  *(undefined4 *)(param_2 + 8) = uVar2;
  uVar2 = wlan_config_get_rts_len_thld(param_1);
  *(undefined4 *)(param_2 + 0x10) = uVar2;
  uVar1 = wlan_config_get_rts_pkt_thld(param_1);
  param_2[0xc] = uVar1;
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb14) != 0)) {
    *(undefined4 *)(*(int *)(param_1 + 0xb14) + 0x10) = *(undefined4 *)(param_2 + 8);
  }
  wlan_operate_set_rts_len_thld(param_1,*(undefined4 *)(param_2 + 0x10));
  wlan_operate_set_rts_pkt_thld(param_1,param_2[0xc]);
  return;
}

