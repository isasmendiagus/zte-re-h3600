// module: mt7915.ko
// function: hw_ctrl_twt_agrt_update @ 0xaede0
// size: 128 bytes
//

undefined4 hw_ctrl_twt_agrt_update(undefined4 param_1,int param_2)

{
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  os_move_mem(&local_3c,*(void **)(param_2 + 8),0x2c);
  asic_twt_agrt_update
            (param_1,local_3c,local_38,local_34,local_30,local_2c,local_28,local_24,local_20,
             local_1c,local_18,local_14);
  return 0;
}

