// module: tm.ko
// function: tm_port_protocol_pktdeal_set @ 0x47340
// size: 720 bytes
//

undefined4
tm_port_protocol_pktdeal_set
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  switch(param_1) {
  case 0:
    uVar1 = 1;
    break;
  case 1:
    uVar1 = 2;
    break;
  case 2:
    uVar1 = 3;
    break;
  case 3:
    uVar1 = 4;
    break;
  case 4:
    uVar1 = 5;
    break;
  case 5:
    uVar1 = 0;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  default:
    printk("tm_port_protocol_pktdeal_set fail, error p_port %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  switch(param_2) {
  case 0:
    uVar4 = 0;
    break;
  case 1:
    uVar4 = 1;
    break;
  case 2:
    uVar4 = 2;
    break;
  case 3:
    uVar4 = 3;
    break;
  default:
    printk("tm_port_protocol_pktdeal_set fail, error deal %d\n");
    return 0xffffffff;
  }
  switch(param_3) {
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
  case 0x10:
    uVar3 = 0x10;
    break;
  case 0x11:
    uVar3 = 0x11;
    break;
  case 0x12:
    uVar3 = 0x12;
    break;
  case 0x13:
    uVar3 = 0x13;
    break;
  case 0x14:
    uVar3 = 0x14;
    break;
  case 0x15:
    uVar3 = 0x15;
    break;
  case 0x16:
    uVar3 = 0x16;
    break;
  case 0x17:
    uVar3 = 0x17;
    break;
  case 0x18:
    uVar3 = 0x18;
    break;
  case 0x19:
    uVar3 = 0x19;
    break;
  case 0x1a:
    uVar3 = 0x1a;
    break;
  case 0x1b:
    uVar3 = 0x1b;
    break;
  case 0x1c:
    uVar3 = 0x1c;
    break;
  case 0x1d:
    uVar3 = 0x1d;
    break;
  case 0x1e:
    uVar3 = 0x1e;
    break;
  case 0x1f:
    uVar3 = 0x1f;
    break;
  case 0x20:
    uVar3 = 0x20;
    break;
  case 0x21:
    uVar3 = 0x21;
    break;
  case 0x22:
    uVar3 = 0x22;
    break;
  case 0x23:
    uVar3 = 0x23;
    break;
  case 0x24:
    uVar3 = 0x24;
    break;
  case 0x25:
    uVar3 = 0x25;
    break;
  case 0x26:
    uVar3 = 0x26;
    break;
  case 0x27:
    uVar3 = 0x27;
    break;
  case 0x28:
    uVar3 = 0x28;
    break;
  case 0x29:
    uVar3 = 0x29;
    break;
  case 0x2a:
    uVar3 = 0x2a;
    break;
  case 0x2b:
    uVar3 = 0x2b;
    break;
  case 0x2c:
    uVar3 = 0x2c;
    break;
  case 0x2d:
    uVar3 = 0x2d;
    break;
  case 0x2e:
    uVar3 = 0x2e;
    break;
  case 0x2f:
    uVar3 = 0x2f;
    break;
  case 0x30:
    uVar3 = 0x30;
    break;
  case 0x31:
    uVar3 = 0x31;
    break;
  case 0x32:
    uVar3 = 0x32;
    break;
  case 0x33:
    uVar3 = 0x33;
    break;
  case 0x34:
    uVar3 = 0x34;
    break;
  case 0x35:
    uVar3 = 0x35;
    break;
  case 0x36:
    uVar3 = 0x36;
    break;
  case 0x37:
    uVar3 = 0x37;
    break;
  case 0x38:
    uVar3 = 0x38;
    break;
  case 0x39:
    uVar3 = 0x39;
    break;
  case 0x3a:
    uVar3 = 0x3a;
    break;
  case 0x3b:
    uVar3 = 0x3b;
    break;
  case 0x3c:
    uVar3 = 0x3c;
    break;
  default:
    printk("protocol fail, error deal %d\n",param_3,param_3,uVar4,param_4);
    return 0xffffffff;
  }
  iVar2 = spa_set_enty_pktdeal_cfg(uVar1,uVar3,uVar4);
  if (iVar2 != 0) {
    printk("tm_port_protocol_pktdeal_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

