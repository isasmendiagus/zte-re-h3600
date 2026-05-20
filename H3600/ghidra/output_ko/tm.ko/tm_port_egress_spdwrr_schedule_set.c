// module: tm.ko
// function: tm_port_egress_spdwrr_schedule_set @ 0x46da8
// size: 120 bytes
//

undefined4
tm_port_egress_spdwrr_schedule_set(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_1 < 8) {
    iVar1 = sch_set_dn_que_sp_dwrr_cfg(param_1,param_2,param_3 != 0);
    if ((iVar1 == 0) &&
       (iVar1 = sch_set_dn_queue_wrr_weight(param_1,param_2,param_4 << 8), iVar1 == 0)) {
      return 0;
    }
    printk("tm_port_egress_spdwrr_schedule_set fail\n");
  }
  else {
    printk("tm_port_egress_spdwrr_schedule_set fail, error port %d\n",param_1,param_3,param_4,
           param_4);
  }
  return 0xffffffff;
}

