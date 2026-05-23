// module: tm.ko
// function: tm_port_unknwn_unicast_flood_get @ 0x50168
// size: 260 bytes
//

undefined4 tm_port_unknwn_unicast_flood_get(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  int local_18 [3];
  
  local_1c = 0;
  if (param_2 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x1416);
    printk("param pp_ena is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = getPort(param_1,local_18);
    if ((iVar1 == 0) && (local_18[0] != 8)) {
      iVar1 = sbrg_get_unknown_unicst_pktdeal(local_18[0],&local_1c);
      if (iVar1 == 0) {
        switch(local_1c) {
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
        printk("tm_port_unknwn_unicast_flood_get fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("tm_port_unknwn_unicast_flood_get fail, error port %d\n",param_1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

