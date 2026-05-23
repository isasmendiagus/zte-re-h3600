// module: tm.ko
// function: tm_tcont_que_secsch_weight_set @ 0x545e0
// size: 196 bytes
//

undefined4 tm_tcont_que_secsch_weight_set(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int local_1c [2];
  
  local_1c[0] = 1;
  sch_get_secsch_sp_dwrr_cfg(param_1,param_2,local_1c);
  if (local_1c[0] == 1) {
    if (1 < g_tm_debug_level) {
      printk("[TM][API][tm_tcont_que_secsch_weight_set]SchMode is SP, Don\'t need cfg weight!\n");
    }
  }
  else {
    if (param_3 == 0) {
      uVar2 = sch_set_quesch_sharp_bucket_cap(param_1,param_2,0);
      uVar1 = sch_set_secsch_wrr_weight(param_1,param_2,1);
      uVar1 = uVar1 | uVar2;
    }
    else {
      uVar1 = sch_set_secsch_wrr_weight(param_1,param_2,param_3 << 8);
    }
    if (uVar1 != 0) {
      printk("tm_tcont_que_secsch_weight_set fail\n");
      return 0xffffffff;
    }
  }
  return 0;
}

