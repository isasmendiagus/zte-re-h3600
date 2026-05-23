// module: tm.ko
// function: tm_port_egress_spdwrr_schedule_get @ 0x46e20
// size: 160 bytes
//

undefined4
tm_port_egress_spdwrr_schedule_get
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_20;
  uint local_1c;
  
  local_20 = 1;
  iVar1 = sch_get_dn_que_sp_dwrr_cfg(param_1,param_2,&local_20);
  if (iVar1 == 0) {
    *(bool *)param_3 = local_20 == 1;
    iVar1 = sch_get_dn_queue_wrr_weight(param_1,param_2,&local_1c);
    if (iVar1 == 0) {
      *param_4 = local_1c >> 8;
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
      printk("tm_port_egress_traffic_police_get dwrr_weight fail\n");
    }
  }
  else {
    uVar2 = 0xffffffff;
    printk("tm_port_egress_traffic_police_get SchMod fail\n");
  }
  return uVar2;
}

