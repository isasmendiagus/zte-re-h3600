// module: tm.ko
// function: zte_api_pp_set_pro_action @ 0x6144c
// size: 1224 bytes
//

int zte_api_pp_set_pro_action(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  bool bVar7;
  
  bVar7 = 2 < param_3;
  bVar6 = param_3 == 3;
  if (param_3 < 4) {
    bVar7 = 0x47 < param_2;
    bVar6 = param_2 == 0x48;
  }
  if (1 < param_1 || bVar7 && !bVar6) {
    if (g_tm_debug_level != 0) {
      printk("[TM][zte_zx_api_pp_set_pro_action]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (param_1 == 0) {
    switch(param_2) {
    case 0:
      uVar5 = 0;
      break;
    case 1:
      uVar5 = 1;
      break;
    case 2:
      uVar5 = 2;
      break;
    case 3:
      uVar5 = 3;
      break;
    case 4:
      uVar5 = 4;
      break;
    case 5:
      uVar5 = 5;
      break;
    case 6:
      uVar5 = 6;
      break;
    case 7:
      uVar5 = 7;
      break;
    case 8:
      uVar5 = 8;
      break;
    case 9:
      uVar5 = 9;
      break;
    case 10:
      uVar5 = 10;
      break;
    case 0xb:
      uVar5 = 0x27;
      break;
    case 0xc:
      uVar5 = 0x10;
      break;
    case 0xd:
    case 0x11:
    case 0x1b:
    case 0x22:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x2a:
    case 0x2d:
    case 0x2e:
    case 0x45:
    case 0x47:
    case 0x48:
switchD_00061480_caseD_d:
      return 0;
    case 0xe:
      uVar5 = 0x13;
      break;
    case 0xf:
      uVar5 = 0x14;
      break;
    case 0x10:
      uVar5 = 0x15;
      break;
    case 0x12:
      uVar5 = 0xd;
      break;
    case 0x13:
      uVar5 = 0x19;
      break;
    case 0x14:
      uVar5 = 0x18;
      break;
    case 0x15:
      uVar5 = 0x1a;
      break;
    case 0x16:
      uVar5 = 0x1b;
      break;
    case 0x17:
      uVar5 = 0x1d;
      break;
    case 0x18:
      uVar5 = 0x1c;
      break;
    case 0x19:
      uVar5 = 0x1e;
      break;
    case 0x1a:
      uVar5 = 0x16;
      break;
    case 0x1c:
      uVar5 = 0xb;
      break;
    case 0x1d:
      uVar5 = 0x20;
      break;
    case 0x1e:
      uVar5 = 0xc;
      break;
    case 0x1f:
      uVar5 = 0x1f;
      break;
    case 0x20:
      uVar5 = 0x17;
      break;
    case 0x21:
      uVar5 = 0xe;
      break;
    case 0x23:
      uVar5 = 0x24;
      break;
    case 0x24:
      uVar5 = 0x22;
      break;
    case 0x25:
      uVar5 = 0x23;
      break;
    case 0x29:
      uVar5 = 0x29;
      break;
    default:
      printk("protocal fail, error deal %d\n");
      return -1;
    case 0x2c:
      uVar5 = 0x21;
      break;
    case 0x2f:
      uVar5 = 0x38;
      break;
    case 0x30:
      uVar5 = 0x37;
      break;
    case 0x31:
      uVar5 = 0x36;
      break;
    case 0x32:
      uVar5 = 0x35;
      break;
    case 0x33:
      uVar5 = 0x34;
      break;
    case 0x34:
      uVar5 = 0x33;
      break;
    case 0x35:
      uVar5 = 0x32;
      break;
    case 0x36:
      uVar5 = 0x31;
      break;
    case 0x37:
      uVar5 = 0x30;
      break;
    case 0x38:
      uVar5 = 0x2f;
      break;
    case 0x39:
      uVar5 = 0x2e;
      break;
    case 0x3a:
      uVar5 = 0x2d;
      break;
    case 0x3b:
      uVar5 = 0x3c;
      break;
    case 0x3c:
      uVar5 = 0x3b;
      break;
    case 0x3d:
      uVar5 = 0x3a;
      break;
    case 0x3e:
      uVar5 = 0x39;
      break;
    case 0x3f:
      uVar5 = 0xf;
      break;
    case 0x40:
      uVar5 = 0x12;
      break;
    case 0x41:
      uVar5 = 0x11;
      break;
    case 0x42:
      uVar5 = 0x2a;
      break;
    case 0x43:
      uVar5 = 0x25;
      break;
    case 0x44:
      uVar5 = 0x26;
      break;
    case 0x46:
      uVar5 = 0x2b;
    }
    uVar2 = 0;
    iVar4 = 0;
    do {
      if (iVar4 == 5) {
        iVar4 = 7;
        uVar1 = tm_port_protocol_pktdeal_set(6,param_3,uVar5);
        uVar2 = uVar2 | uVar1;
      }
      iVar3 = iVar4 + 1;
      uVar1 = tm_port_protocol_pktdeal_set(iVar4,param_3,uVar5);
      uVar2 = uVar2 | uVar1;
      iVar4 = iVar3;
    } while (iVar3 < 8);
    return -(uint)(uVar2 != 0);
  }
  switch(param_2) {
  case 0:
    uVar5 = 0;
    break;
  case 1:
    uVar5 = 1;
    break;
  case 2:
    uVar5 = 2;
    break;
  case 3:
    uVar5 = 3;
    break;
  case 4:
    uVar5 = 4;
    break;
  case 5:
    uVar5 = 5;
    break;
  case 6:
    uVar5 = 6;
    break;
  case 7:
    uVar5 = 7;
    break;
  case 8:
    uVar5 = 8;
    break;
  case 9:
    uVar5 = 9;
    break;
  case 10:
    uVar5 = 10;
    break;
  case 0xb:
    uVar5 = 0x27;
    break;
  case 0xc:
    uVar5 = 0x10;
    break;
  case 0xd:
  case 0x11:
  case 0x1b:
  case 0x26:
  case 0x27:
  case 0x29:
  case 0x2b:
  case 0x2d:
  case 0x2e:
  case 0x3f:
    goto switchD_00061480_caseD_d;
  case 0xe:
    uVar5 = 0x13;
    break;
  case 0xf:
    uVar5 = 0x14;
    break;
  case 0x10:
    uVar5 = 0x15;
    break;
  case 0x12:
    uVar5 = 0xd;
    break;
  case 0x13:
    uVar5 = 0x19;
    break;
  case 0x14:
    uVar5 = 0x18;
    break;
  case 0x15:
    uVar5 = 0x1a;
    break;
  case 0x16:
    uVar5 = 0x1b;
    break;
  case 0x17:
    uVar5 = 0x1d;
    break;
  case 0x18:
    uVar5 = 0x1c;
    break;
  case 0x19:
    uVar5 = 0x1e;
    break;
  case 0x1a:
    uVar5 = 0x16;
    break;
  case 0x1c:
    uVar5 = 0xb;
    break;
  case 0x1d:
    uVar5 = 0x20;
    break;
  case 0x1e:
    uVar5 = 0xc;
    break;
  default:
    printk("tm_pon_protocol_pktdeal_set fail, error protocal %d\n");
    return -1;
  case 0x20:
    uVar5 = 0x17;
    break;
  case 0x28:
    uVar5 = 0x42;
    break;
  case 0x2a:
    uVar5 = 0x41;
    break;
  case 0x2c:
    uVar5 = 0x21;
    break;
  case 0x2f:
    uVar5 = 0x38;
    break;
  case 0x30:
    uVar5 = 0x37;
    break;
  case 0x31:
    uVar5 = 0x36;
    break;
  case 0x32:
    uVar5 = 0x35;
    break;
  case 0x33:
    uVar5 = 0x34;
    break;
  case 0x34:
    uVar5 = 0x33;
    break;
  case 0x35:
    uVar5 = 0x32;
    break;
  case 0x36:
    uVar5 = 0x31;
    break;
  case 0x37:
  case 0x3a:
    uVar5 = 0x2d;
    break;
  case 0x38:
    uVar5 = 0x2f;
    break;
  case 0x39:
    uVar5 = 0x2e;
    break;
  case 0x3b:
    uVar5 = 0x3c;
    break;
  case 0x3c:
    uVar5 = 0x3b;
    break;
  case 0x3d:
    uVar5 = 0x3a;
    break;
  case 0x3e:
    uVar5 = 0x39;
    break;
  case 0x40:
    uVar5 = 0x12;
    break;
  case 0x41:
    uVar5 = 0x11;
    break;
  case 0x42:
    uVar5 = 0x2a;
    break;
  case 0x43:
    uVar5 = 0x25;
    break;
  case 0x44:
    uVar5 = 0x26;
    break;
  case 0x46:
    uVar5 = 0x2b;
  }
  iVar4 = tm_port_protocol_pktdeal_set(5,param_3,uVar5,0,param_4);
  if (iVar4 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][dpa_set_protocol_type_i_act] failed\n");
    return -1;
  }
  return -1;
}

