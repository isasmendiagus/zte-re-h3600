// module: tm.ko
// function: zte_api_sw_mac_set_onu_proaction @ 0x626d8
// size: 252 bytes
//

undefined4 zte_api_sw_mac_set_onu_proaction(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  switch(param_1) {
  case 0:
  case 1:
    uVar5 = 4;
    break;
  case 2:
    uVar5 = 1;
    break;
  case 3:
    uVar5 = 7;
    break;
  case 4:
    uVar5 = 10;
    break;
  case 5:
    uVar5 = 9;
    break;
  case 6:
    uVar5 = 6;
    break;
  case 7:
    uVar5 = 8;
    break;
  case 8:
    uVar5 = 0x1a;
    break;
  case 9:
    uVar5 = 0x1c;
    break;
  case 10:
    uVar5 = 0x1b;
    break;
  case 0xb:
    uVar5 = 0x1d;
    break;
  default:
    printk("invaild pkt type\n");
    return 0xffffffff;
  }
  if (param_2 != 1) {
    if (param_2 == 0) {
      param_2 = 0;
    }
    else if (param_2 != 2) {
      printk("invaid action type\n");
      return 0xffffffff;
    }
  }
  uVar4 = 0;
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    uVar1 = spa_set_enty_pktdeal_cfg(param_2,uVar5,iVar2);
    uVar4 = uVar4 | uVar1;
    iVar2 = iVar3;
  } while (iVar3 != 8);
  if (uVar4 != 0) {
    printk("[%s]tm sdk failed!\n","zte_api_sw_mac_set_onu_proaction");
    return 0xffffffff;
  }
  return 0;
}

