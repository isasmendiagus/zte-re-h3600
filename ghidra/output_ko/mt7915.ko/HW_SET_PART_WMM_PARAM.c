// module: mt7915.ko
// function: HW_SET_PART_WMM_PARAM @ 0xb1990
// size: 124 bytes
//

void HW_SET_PART_WMM_PARAM
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_18[0] = (undefined1)param_2;
  local_c = param_5;
  local_14 = param_3;
  local_10 = param_4;
  if (2 < DebugLevel) {
    printk("%s: wmm_idx=%x, ac_num=%x, edca_type=%x, edca_value=%x\n","HW_SET_PART_WMM_PARAM",
           param_2,param_3,param_4,param_5);
  }
  FUN_000b0a74(param_1,6,0x3c,0x10,local_18);
  return;
}

