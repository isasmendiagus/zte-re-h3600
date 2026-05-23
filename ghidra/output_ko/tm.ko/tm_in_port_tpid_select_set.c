// module: tm.ko
// function: tm_in_port_tpid_select_set @ 0x48568
// size: 460 bytes
//

undefined4
tm_in_port_tpid_select_set
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  switch(param_1) {
  case 0:
    uVar1 = 2;
    break;
  case 1:
    uVar1 = 3;
    break;
  case 2:
    uVar1 = 4;
    break;
  case 3:
    uVar1 = 5;
    break;
  case 4:
    uVar1 = 6;
    break;
  case 5:
    uVar1 = 1;
    break;
  case 6:
    uVar1 = 0;
    break;
  case 7:
    uVar1 = 7;
    break;
  case 8:
    uVar1 = 8;
    break;
  default:
    printk("tm_in_port_tpid_select_set fail, error p_port %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  switch(param_2) {
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
  case 5:
    uVar4 = 5;
    break;
  case 6:
    uVar4 = 6;
    break;
  case 7:
    uVar4 = 7;
    break;
  default:
    printk("tm_in_port_tpid_select_set fail, error num %d\n");
    return 0xffffffff;
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
    printk("tm_in_port_tpid_select_set fail, error select %d\n",param_3,param_3,uVar4,param_4);
    return 0xffffffff;
  }
  iVar2 = spa_set_tpid_i_sel_i(uVar1,uVar3,uVar4);
  if (iVar2 != 0) {
    printk("tm_up_tpid_select_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

