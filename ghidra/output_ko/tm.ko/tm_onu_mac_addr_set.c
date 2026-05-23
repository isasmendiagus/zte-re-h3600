// module: tm.ko
// function: tm_onu_mac_addr_set @ 0x4c1a8
// size: 332 bytes
//

undefined4 tm_onu_mac_addr_set(undefined1 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  if (param_1 == (undefined1 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x4801);
    printk("param pp_onu_mac is NULL\n");
    uVar3 = 0xffffffff;
  }
  else {
    local_16 = param_1[1];
    local_15 = param_1[2];
    local_14 = param_1[3];
    local_13 = param_1[4];
    local_12 = param_1[5];
    local_11 = param_1[6];
    switch(*param_1) {
    case 0:
      uVar3 = 0;
      break;
    case 1:
      uVar3 = 1;
      break;
    case 2:
      uVar3 = 2;
      break;
    case 3:
      uVar3 = 3;
      break;
    case 4:
      uVar3 = 4;
      break;
    case 5:
      uVar3 = 5;
      break;
    case 6:
      uVar3 = 6;
      break;
    case 7:
      uVar3 = 7;
      break;
    case 8:
      uVar3 = 8;
      break;
    case 9:
      uVar3 = 9;
      break;
    case 10:
      uVar3 = 10;
      break;
    case 0xb:
      uVar3 = 0xb;
      break;
    case 0xc:
      uVar3 = 0xc;
      break;
    case 0xd:
      uVar3 = 0xd;
      break;
    case 0xe:
      uVar3 = 0xe;
      break;
    case 0xf:
      uVar3 = 0xf;
      break;
    default:
      printk("invalid param\n");
      return 1;
    }
    iVar1 = spa_set_onu_mac_addr(uVar3,&local_16);
    iVar2 = pp_pm_set_onu_mac_ram_info(uVar3,&local_16);
    uVar3 = 0;
    if (iVar2 != 0 || iVar1 != 0) {
      printk("tm_onu_mac_addr_set fail\n");
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

