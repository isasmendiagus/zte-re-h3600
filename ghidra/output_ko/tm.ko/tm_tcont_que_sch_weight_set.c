// module: tm.ko
// function: tm_tcont_que_sch_weight_set @ 0x4be54
// size: 280 bytes
//

undefined4 tm_tcont_que_sch_weight_set(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int local_20;
  int local_1c;
  
  local_1c = 1;
  local_20 = 0;
  sch_get_up_que_sp_dwrr_cfg(param_1,param_2,&local_1c);
  if (local_1c == 1) {
    if (1 < g_tm_debug_level) {
      printk("[TM][API][tm_tcont_que_sch_weight_set]SchMode is SP, Don\'t need cfg weight!\n");
      return 0;
    }
  }
  else {
    if (param_3 == 0) {
      uVar1 = sch_set_up_pq_sharp_bucket_cap(param_1,param_2,0);
      uVar2 = sch_set_up_queue_wrr_weight(param_1,param_2,1);
      uVar2 = uVar2 | uVar1;
    }
    else {
      printk("\n---p_que_weight=%d",param_3);
      uVar1 = sch_set_up_queue_wrr_weight(param_1,param_2,param_3 << 8);
      uVar2 = sch_get_up_pq_sharp_bucket_cap(param_1,param_2,&local_20);
      if (local_20 == 0) {
        uVar2 = sch_set_up_pq_sharp_bucket_cap(param_1,param_2,200000);
      }
      else {
        uVar2 = uVar2 | uVar1;
      }
    }
    if (uVar2 != 0) {
      printk("tm_tcont_que_sch_weight_set fail\n");
      return 0xffffffff;
    }
  }
  return 0;
}

