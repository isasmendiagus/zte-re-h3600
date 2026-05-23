// module: tm.ko
// function: tm_port_stp_get @ 0x482c8
// size: 216 bytes
//

undefined4 tm_port_stp_get(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_20;
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
    printk("tm_port_stp_get fail, error p_port %d\n",param_1);
    return 0xffffffff;
  case 6:
    uVar3 = 5;
    break;
  case 7:
    uVar3 = 6;
  }
  iVar1 = greg_get_port_stp_en(uVar3,&local_20);
  iVar2 = greg_get_port_sel_stp_rstp(uVar3,local_1c);
  if (iVar2 == 0 && iVar1 == 0) {
    *(bool *)param_2 = local_20 != 0;
    *(bool *)param_3 = local_1c[0] != 0;
    uVar3 = 0;
  }
  else {
    printk("tm_port_stp_get fail\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

