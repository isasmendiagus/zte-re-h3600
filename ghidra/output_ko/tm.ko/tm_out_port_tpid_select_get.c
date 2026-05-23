// module: tm.ko
// function: tm_out_port_tpid_select_get @ 0x48a5c
// size: 532 bytes
//

undefined4 tm_out_port_tpid_select_get(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_c;
  
  local_c = 0;
  switch(param_1) {
  case 0:
    uVar1 = 1;
    break;
  case 1:
    uVar1 = 2;
    break;
  case 2:
    uVar1 = 3;
    break;
  case 3:
    uVar1 = 4;
    break;
  case 4:
    uVar1 = 5;
    break;
  case 5:
    uVar1 = 0;
    break;
  default:
    printk("tm_out_port_tpid_select_get fail, error p_port %d\n",param_1);
    return 0xffffffff;
  case 7:
    uVar1 = 6;
    break;
  case 8:
    uVar1 = 7;
  }
  switch(param_3) {
  case 0:
    uVar4 = 0;
    uVar3 = 0;
    break;
  case 1:
    uVar4 = 1;
    uVar3 = 0;
    break;
  case 2:
    uVar4 = 2;
    uVar3 = 0;
    break;
  case 3:
    uVar4 = 3;
    uVar3 = 0;
    break;
  case 4:
    uVar4 = 0;
    uVar3 = 1;
    break;
  case 5:
    uVar4 = 1;
    uVar3 = 1;
    break;
  case 6:
    uVar4 = 2;
    uVar3 = 1;
    break;
  case 7:
    uVar4 = 3;
    uVar3 = 1;
    break;
  case 8:
    uVar4 = 0;
    uVar3 = 2;
    break;
  case 9:
    uVar4 = 1;
    uVar3 = 2;
    break;
  case 10:
    uVar4 = 2;
    uVar3 = 2;
    break;
  case 0xb:
    uVar4 = 3;
    uVar3 = 2;
    break;
  case 0xc:
    uVar4 = 0;
    uVar3 = 3;
    break;
  case 0xd:
    uVar4 = 1;
    uVar3 = 3;
    break;
  case 0xe:
    uVar4 = 2;
    uVar3 = 3;
    break;
  case 0xf:
    uVar3 = 3;
    uVar4 = uVar3;
    break;
  default:
    printk("tm_out_port_tpid_select_get fail, error select %d\n",param_3);
    return 0xffffffff;
  }
  iVar2 = dpa_get_tpid_i_sel_i(uVar1,uVar3,uVar4,&local_c);
  if (iVar2 == 0) {
    switch(local_c) {
    case 0:
      uVar1 = 0;
      *param_2 = 0;
      break;
    case 1:
      uVar1 = 0;
      *param_2 = 1;
      break;
    case 2:
      uVar1 = 0;
      *param_2 = 2;
      break;
    case 3:
      uVar1 = 0;
      *param_2 = 3;
      break;
    case 4:
      uVar1 = 0;
      *param_2 = 4;
      break;
    case 5:
      uVar1 = 0;
      *param_2 = 5;
      break;
    case 6:
      uVar1 = 0;
      *param_2 = 6;
      break;
    case 7:
      uVar1 = 0;
      *param_2 = 7;
      break;
    default:
      uVar1 = 0;
    }
  }
  else {
    printk("tm_out_port_tpid_select_get fail\n");
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

