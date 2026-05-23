// module: tm.ko
// function: tm_mac_learn_mode_set @ 0x46020
// size: 204 bytes
//

undefined4 tm_mac_learn_mode_set(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
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
    uVar3 = 0;
    break;
  case 6:
    uVar3 = 6;
    break;
  case 7:
    uVar3 = 7;
    break;
  default:
    printk("tm_mac_learn_mode_set fail, error port %d\n",param_1);
    uVar3 = 1;
  }
  switch(param_2) {
  case 0:
    uVar2 = 0;
    break;
  case 1:
    uVar2 = 1;
    break;
  case 2:
    uVar2 = 2;
    break;
  case 3:
    uVar2 = 3;
    break;
  default:
    printk("tm_mac_learn_mode_set fail, error mode %d\n",param_2);
    return 0xffffffff;
  }
  iVar1 = sbrg_set_pt_learn_mode(uVar2,uVar3);
  if (iVar1 != 0) {
    printk("tm_mac_learn_mode_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

