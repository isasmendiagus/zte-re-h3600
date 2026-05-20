// module: tm.ko
// function: tm_mac_learn_mode_get @ 0x4a32c
// size: 300 bytes
//

undefined4 tm_mac_learn_mode_get(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  local_c = 0;
  if (param_2 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2a8d);
    printk("param pp_mode is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
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
      printk("tm_mac_learn_mode_get fail, error port %d\n",param_1);
      uVar2 = 1;
    }
    iVar1 = sbrg_get_pt_learn_mode(&local_c,uVar2);
    if (iVar1 == 0) {
      switch(local_c) {
      case 0:
        *param_2 = 0;
        return 0;
      case 1:
        *param_2 = 1;
        return 0;
      case 2:
        *param_2 = 2;
        return 0;
      case 3:
        uVar2 = 0;
        *param_2 = 3;
        break;
      default:
        uVar2 = 0;
      }
    }
    else {
      printk("tm_mac_learn_mode_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

