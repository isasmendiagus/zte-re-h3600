// module: mt7915.ko
// function: he_oper_init @ 0x2060ac
// size: 64 bytes
//

void he_oper_init(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = wlan_config_get_ppdu_caps();
  param_2[1] = 0;
  *param_2 = 1;
  param_2[2] = 1;
  uVar2 = wlan_config_get_he_txop_dur_rts_thld(param_1);
  *(undefined4 *)(param_2 + 8) = uVar2;
  param_2[0xc] = *(undefined1 *)(iVar1 + 0x18);
  return;
}

