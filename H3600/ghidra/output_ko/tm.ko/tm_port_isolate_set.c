// module: tm.ko
// function: tm_port_isolate_set @ 0x469d0
// size: 168 bytes
//

undefined4
tm_port_isolate_set(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
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
    printk("tm_port_isolate_set fail, error p_isolateReg %d\n",param_1,param_1,param_2,param_4);
    return 0xffffffff;
  }
  param_2 = ~param_2;
  iVar1 = sbrg_set_isolate_pt_cfg
                    ((param_2 << 0x1a) >> 0x1f | (param_2 & 0x1f) << 1 | param_2 & 0xc0,uVar2);
  if (iVar1 != 0) {
    printk("tm_port_isolate_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

