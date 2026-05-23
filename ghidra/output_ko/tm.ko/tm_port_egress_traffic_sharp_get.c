// module: tm.ko
// function: tm_port_egress_traffic_sharp_get @ 0x46ec0
// size: 184 bytes
//

undefined4 tm_port_egress_traffic_sharp_get(uint param_1,undefined1 *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_18;
  int local_14;
  
  local_18 = 0;
  local_14 = 0;
  if (param_1 < 8) {
    iVar1 = sch_get_dn_tcont_sharp_fill_rate(param_1,&local_18);
    if (iVar1 == 0) {
      uVar2 = 0;
      if (local_18 == 0x1f4000) {
        *param_2 = 0;
      }
      else {
        *param_3 = local_18;
        iVar1 = sch_get_tcont_sharp_enable(&local_14);
        if (iVar1 == 0) {
          *param_2 = local_14 != 0;
        }
        else {
          uVar2 = 0xffffffff;
          printk("tm_port_egress_traffic_sharp_get port_ena fail\n");
        }
      }
    }
    else {
      uVar2 = 0xffffffff;
      printk("tm_port_egress_traffic_sharp_get fail\n");
    }
  }
  else {
    uVar2 = 0xffffffff;
    printk("tm_port_egress_traffic_sharp_set fail, error port %d\n",param_1);
  }
  return uVar2;
}

