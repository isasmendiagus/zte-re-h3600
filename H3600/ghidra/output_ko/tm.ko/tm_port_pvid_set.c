// module: tm.ko
// function: tm_port_pvid_set @ 0x465f4
// size: 184 bytes
//

undefined4 tm_port_pvid_set(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  switch(param_1) {
  case 0:
    uVar3 = 1;
    break;
  case 1:
    uVar3 = 2;
    break;
  case 2:
    uVar3 = 3;
    break;
  case 3:
    uVar3 = 4;
    break;
  case 4:
    uVar3 = 5;
    break;
  case 5:
    iVar1 = spa_set_port_dft_pri(0,param_3);
    if (iVar1 == 0) {
      return 0;
    }
    goto LAB_00046658;
  case 6:
    uVar3 = 6;
    break;
  case 7:
    uVar3 = 7;
    break;
  default:
    printk("tm_port_pvid_set fail, error port %d\n",param_1);
    return 0xffffffff;
  }
  iVar1 = spa_set_port_dft_pri(uVar3,param_3);
  iVar2 = spa_set_port_up_untag_pvid(uVar3,param_2);
  if (iVar2 == 0 && iVar1 == 0) {
    return 0;
  }
LAB_00046658:
  printk("tm_port_pvid_set fail\n");
  return 0xffffffff;
}

