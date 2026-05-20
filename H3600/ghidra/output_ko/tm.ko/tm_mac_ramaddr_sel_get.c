// module: tm.ko
// function: tm_mac_ramaddr_sel_get @ 0x4c61c
// size: 204 bytes
//

undefined4 tm_mac_ramaddr_sel_get(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  local_c = 0;
  if (param_1 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2e9a);
    printk("param pp_sel is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_get_table_sel(&local_c);
    if (iVar1 == 0) {
      switch(local_c) {
      case 0:
        *param_1 = 0;
        return 0;
      case 1:
        *param_1 = 1;
        return 0;
      case 2:
        *param_1 = 2;
        return 0;
      case 3:
        uVar2 = 0;
        *param_1 = 3;
        break;
      default:
        uVar2 = 0;
      }
    }
    else {
      printk("tm_mac_ramaddr_sel_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

