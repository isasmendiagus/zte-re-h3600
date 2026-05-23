// module: tm.ko
// function: tm_port_unknwn_multicast_floodport_get @ 0x4ff68
// size: 288 bytes
//

undefined4 tm_port_unknwn_multicast_floodport_get(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_1c;
  int local_18 [2];
  
  local_1c = 0;
  if (param_2 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x138b);
    printk("param pp_ena is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = getPort(param_1,local_18);
    if ((iVar1 == 0) && (local_18[0] != 8)) {
      switch(param_3) {
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
        printk("tm_port_unknwn_multicast_floodport_get fail, error pt_cfg %d\n",param_3);
        return 0xffffffff;
      }
      iVar1 = sbrg_get_uni_unkmul_fld_inctrl(local_18[0],&local_1c,uVar2);
      if (iVar1 == 0) {
        *(bool *)param_2 = local_1c != 0;
        uVar2 = 0;
      }
      else {
        printk("tm_port_unknwn_multicast_floodport_get fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("tm_port_unknwn_multicast_floodport_get fail, error port %d\n",param_1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

