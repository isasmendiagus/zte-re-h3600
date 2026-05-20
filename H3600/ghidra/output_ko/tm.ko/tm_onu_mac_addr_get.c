// module: tm.ko
// function: tm_onu_mac_addr_get @ 0x4c334
// size: 264 bytes
//

undefined4 tm_onu_mac_addr_get(undefined1 *param_1)

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
  case 4:
    uVar2 = 4;
    break;
  case 5:
    uVar2 = 5;
    break;
  case 6:
    uVar2 = 6;
    break;
  case 7:
    uVar2 = 7;
    break;
  case 8:
    uVar2 = 8;
    break;
  case 9:
    uVar2 = 9;
    break;
  case 10:
    uVar2 = 10;
    break;
  case 0xb:
    uVar2 = 0xb;
    break;
  case 0xc:
    uVar2 = 0xc;
    break;
  case 0xd:
    uVar2 = 0xd;
    break;
  case 0xe:
    uVar2 = 0xe;
    break;
  case 0xf:
    uVar2 = 0xf;
    break;
  default:
    printk("invalid param\n");
    return 1;
  }
  iVar1 = spa_get_onu_mac_addr(uVar2,&local_16);
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
    printk("tm_onu_mac_addr_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

