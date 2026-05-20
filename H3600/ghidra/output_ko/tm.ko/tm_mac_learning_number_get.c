// module: tm.ko
// function: tm_mac_learning_number_get @ 0x4c92c
// size: 188 bytes
//

undefined4
tm_mac_learning_number_get(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2c37,0,param_4);
    printk("param pp_num is NULL\n");
    return 0xffffffff;
  }
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
  case 5:
    uVar2 = 0;
    break;
  case 6:
    uVar2 = 6;
    break;
  case 7:
    uVar2 = 7;
    break;
  default:
    printk("tm_mac_learning_number_get fail, error p_port %d\n",param_1,param_3,param_2,param_4);
    return 0xffffffff;
  }
  iVar1 = sbrg_get_macaddr_ln_statistics(param_2,uVar2);
  if (iVar1 != 0) {
    printk("tm_mac_learning_number_get fail\n");
    return 0xffffffff;
  }
  return 0;
}

