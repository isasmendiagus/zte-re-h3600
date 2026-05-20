// module: tm.ko
// function: tm_port_flow_send_ctrl_get @ 0x47c1c
// size: 184 bytes
//

undefined4 tm_port_flow_send_ctrl_get(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_1c [2];
  
  local_1c[0] = 0;
  switch(param_1) {
  case 0:
    uVar3 = 0;
    break;
  case 1:
    uVar3 = 1;
    break;
  case 2:
    uVar3 = 2;
    break;
  case 3:
    uVar3 = 3;
    break;
  case 4:
    uVar3 = 4;
    break;
  default:
    printk("tm_port_flow_send_ctrl_get fail, error mac_num %d\n",param_1);
    return 0xffffffff;
  }
  iVar1 = smac_get_tfe(uVar3,local_1c);
  iVar2 = smac_get_pt(uVar3,param_3);
  if (iVar2 == 0 && iVar1 == 0) {
    *(bool *)param_2 = local_1c[0] != 0;
    uVar3 = 0;
  }
  else {
    printk("tm_port_flow_send_ctrl_get fail\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

