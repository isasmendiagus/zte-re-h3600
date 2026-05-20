// module: tm.ko
// function: tm_port_flow_send_ctrl_set @ 0x47b64
// size: 164 bytes
//

undefined4
tm_port_flow_send_ctrl_set(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  switch(param_1) {
  case 0:
    uVar4 = 0;
    break;
  case 1:
    uVar4 = 1;
    break;
  case 2:
    uVar4 = 2;
    break;
  case 3:
    uVar4 = 3;
    break;
  case 4:
    uVar4 = 4;
    break;
  default:
    printk("tm_port_flow_send_ctrl_set fail, error mac_num %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  iVar1 = smac_set_tfe(uVar4,param_2 != 0);
  iVar2 = smac_set_efc(uVar4,param_2 != 0);
  iVar3 = smac_set_pt(uVar4,param_3);
  if ((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) {
    printk("tm_port_flow_send_ctrl_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

