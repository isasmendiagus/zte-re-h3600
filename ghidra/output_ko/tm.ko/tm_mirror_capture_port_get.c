// module: tm.ko
// function: tm_mirror_capture_port_get @ 0x4aaac
// size: 300 bytes
//

undefined4 tm_mirror_capture_port_get(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  local_c = 1;
  if (param_1 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3374);
    printk("param pp_port is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_get_capture_pt(&local_c);
    if (iVar1 == 0) {
      switch(local_c) {
      case 0:
        *param_1 = 5;
        return 0;
      case 1:
        *param_1 = 0;
        return 0;
      case 2:
        *param_1 = 1;
        return 0;
      case 3:
        *param_1 = 2;
        return 0;
      case 4:
        *param_1 = 3;
        return 0;
      case 5:
        *param_1 = 4;
        return 0;
      case 6:
        *param_1 = 6;
        return 0;
      case 7:
        uVar2 = 0;
        *param_1 = 7;
        break;
      default:
        printk("param l_port %d is invalid\n");
        return 0xffffffff;
      }
    }
    else {
      printk("tm_mirror_capture_port_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

