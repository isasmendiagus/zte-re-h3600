// module: tm.ko
// function: tm_port_unknwn_unicast_flood_set @ 0x500a8
// size: 176 bytes
//

undefined4 tm_port_unknwn_unicast_flood_set(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [3];
  
  iVar1 = getPort(param_1,local_18);
  if ((iVar1 == 0) && (local_18[0] != 8)) {
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
      printk("tm_port_unknwn_unicast_flood_set fail, error p_ctrl %d\n",param_2);
      return 0xffffffff;
    }
    iVar1 = sbrg_set_unknown_unicst_pktdeal(local_18[0],uVar2);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_port_unknwn_unicast_flood_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_port_unknwn_unicast_flood_set fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

