// module: tm.ko
// function: tm_mac_learning_limit_get @ 0x4a608
// size: 248 bytes
//

undefined4 tm_mac_learning_limit_get(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_14;
  
  local_14 = 0;
  if (param_2 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2bb0);
    printk("param pp_ena is NULL\n");
    uVar3 = 0xffffffff;
  }
  else {
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
      printk("tm_mac_learning_limit_get fail, error port %d\n",param_1);
      return 0xffffffff;
    }
    iVar1 = sbrg_get_macaddr_ln_num_limit(param_3,uVar3);
    iVar2 = sbrg_get_pt_learn_limit_en(uVar3,&local_14);
    if (iVar2 == 0 && iVar1 == 0) {
      *(bool *)param_2 = local_14 != 0;
      uVar3 = 0;
    }
    else {
      printk("tm_mac_learning_limit_get fail\n");
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

