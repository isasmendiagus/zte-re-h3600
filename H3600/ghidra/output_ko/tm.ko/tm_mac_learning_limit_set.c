// module: tm.ko
// function: tm_mac_learning_limit_set @ 0x4a524
// size: 196 bytes
//

undefined4
tm_mac_learning_limit_set(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
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
    printk("tm_mac_learning_limit_set fail, error port %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  uVar1 = sbrg_set_pt_learn_limit_en(uVar3,param_2 != 0);
  if (param_2 != 0) {
    uVar2 = sbrg_set_macaddr_ln_num_limit(param_3,uVar3);
    uVar1 = uVar1 | uVar2;
  }
  if (uVar1 == 0) {
    return 0;
  }
  printk("tm_mac_learning_limit_set fail\n");
  return 0xffffffff;
}

