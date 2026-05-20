// module: tm.ko
// function: tm_port_pvid_get @ 0x466cc
// size: 240 bytes
//

undefined4 tm_port_pvid_get(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_3 == 0 || param_2 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x6fe);
    printk("param pp_pvid or pp_pri is NULL\n");
    return 0xffffffff;
  }
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
    iVar1 = spa_get_port_dft_pri(0,param_3);
    if (iVar1 == 0) {
      return 0;
    }
    goto LAB_0004673c;
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
  iVar1 = spa_get_port_dft_pri(uVar3,param_3);
  iVar2 = spa_get_port_up_untag_pvid(uVar3,param_2);
  if (iVar2 == 0 && iVar1 == 0) {
    return 0;
  }
LAB_0004673c:
  printk("tm_port_pvid_get fail\n");
  return 0xffffffff;
}

