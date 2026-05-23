// module: tm.ko
// function: tm_port_802x_trap_set @ 0x463bc
// size: 136 bytes
//

undefined4
tm_port_802x_trap_set(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  switch(param_1) {
  case 0:
    uVar2 = 1;
    break;
  case 1:
    uVar2 = 2;
    break;
  case 2:
    uVar2 = 3;
    break;
  case 3:
    uVar2 = 4;
    break;
  case 4:
    uVar2 = 5;
    break;
  default:
    printk("tm_port_802x_trap_set fail, error p_port %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  case 6:
    uVar2 = 6;
    break;
  case 7:
    uVar2 = 7;
  }
  iVar1 = spa_set_pt_802x_trap_en(uVar2,param_2 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_port_802x_trap_set fail\n");
  return 0xffffffff;
}

