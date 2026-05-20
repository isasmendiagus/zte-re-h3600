// module: mt7915.ko
// function: fill_bssinfo_he @ 0x205e5c
// size: 60 bytes
//

void fill_bssinfo_he(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  
  iVar3 = wlan_config_get_ppdu_caps();
  uVar1 = *(undefined1 *)(iVar3 + 0x19);
  *(undefined1 *)(param_2 + 0x95) = 0;
  *(undefined1 *)(param_2 + 0x94) = uVar1;
  uVar2 = wlan_operate_get_he_txop_dur_rts_thld(param_1);
  *(undefined2 *)(param_2 + 0x96) = uVar2;
  bss_color_init(param_1,param_2);
  return;
}

