// module: tm.ko
// function: tm_soft_protocol_dmac_get @ 0x4714c
// size: 172 bytes
//

undefined4 tm_soft_protocol_dmac_get(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  switch(*param_1) {
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
    printk("invalid param\n");
    return 1;
  }
  iVar1 = spa_get_trap_dmac(uVar2,&local_16);
  if (iVar1 == 0) {
    param_1[1] = local_16;
    param_1[2] = local_15;
    param_1[3] = local_14;
    param_1[4] = local_13;
    param_1[5] = local_12;
    param_1[6] = local_11;
    uVar2 = 0;
  }
  else {
    printk("tm_soft_protocol_dmac_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

