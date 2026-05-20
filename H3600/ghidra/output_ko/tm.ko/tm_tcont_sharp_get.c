// module: tm.ko
// function: tm_tcont_sharp_get @ 0x4bdb4
// size: 76 bytes
//

undefined4 tm_tcont_sharp_get(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  local_c = 0;
  iVar1 = sch_get_up_tcont_sharp_fill_rate(param_1,&local_c);
  if (iVar1 == 0) {
    *param_2 = local_c;
    uVar2 = 0;
  }
  else {
    printk("tm_port_egress_traffic_sharp_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

