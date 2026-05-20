// module: tm.ko
// function: tm_port_isolate_get @ 0x46a98
// size: 228 bytes
//

undefined4 tm_port_isolate_get(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_14 [2];
  
  if (param_2 == (uint *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x9e0);
    printk("param port_mask is NULL\n");
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
      uVar3 = 4;
      break;
    case 3:
      uVar3 = 5;
      break;
    case 4:
      uVar3 = 3;
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
      printk("tm_port_isolate_get fail, error p_isolateReg %d\n",param_1);
      return 0xffffffff;
    }
    iVar1 = sbrg_get_isolate_pt_cfg(local_14,uVar3);
    uVar2 = sbrg_change_portmask(local_14[0]);
    *param_2 = ~uVar2;
    if (iVar1 == 0) {
      uVar3 = 0;
    }
    else {
      printk("tm_port_isolate_get fail\n");
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

