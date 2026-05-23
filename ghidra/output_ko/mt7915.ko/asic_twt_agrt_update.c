// module: mt7915.ko
// function: asic_twt_agrt_update @ 0x134f80
// size: 200 bytes
//

undefined4
asic_twt_agrt_update(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  local_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    AsicNotSupportFunc(param_1,"asic_twt_agrt_update");
    return 0;
  }
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  os_move_mem(&local_4c,&local_c,0x2c);
  uVar2 = mt_cmd_ext_twt_agrt_update
                    (param_1,local_4c,local_48,local_44,local_40,local_3c,local_38,local_34,local_30
                     ,local_2c,local_28,local_24);
  return uVar2;
}

