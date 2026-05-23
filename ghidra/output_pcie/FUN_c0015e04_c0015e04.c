// vmlinux.bin: FUN_c0015e04 @ 0xc0015e04
// matched strings: synopsys pcie probe enter!!!!!!, pcie0 irq is %d, pcie1 irq is %d
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c0015e04(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  
  FUN_c01b1418(0x35,0);
  iVar6 = 10;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  FUN_c01b1418(0x35,1);
  iVar6 = 200;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  FUN_c01b1418(0x37,0);
  iVar6 = 10;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  FUN_c01b1418(0x37,1);
  iVar6 = 200;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar1 = DAT_c0016058;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  FUN_c046ab98(s_synopsys_pcie_probe_enter_______c0585ba0);
  uVar2 = FUN_c01edeec(param_1,0);
  uVar3 = FUN_c01edeec(param_1,2);
  FUN_c046ab98(s_pcie0_irq_is__d_c0585bc4,uVar2);
  uVar4 = FUN_c01edeec(param_1,1);
  uVar5 = FUN_c01edeec(param_1,3);
  FUN_c046ab98(s_pcie1_irq_is__d_c0585bd8,uVar4);
  _DAT_c069ea4c = iVar1 + 0x38;
  _DAT_c069ea48 = iVar1;
  DAT_c069ea19 = 0xff;
  DAT_c069ea18 = 0;
  _DAT_c069ea40 = 0;
  _DAT_c069ea44 = 0;
  _DAT_c069ea24 = 0xf0500000;
  _DAT_c069ea28 = 0xf0400000;
  _DAT_c069ea1c = 0x10000000;
  _DAT_c069ea34 = uVar2;
  _DAT_c069ea38 = uVar3;
  _DAT_c069ea20 = FUN_c00126a4(0xf000000,0x4000,0);
  _DAT_c069ea2c = FUN_c00126a4(0x9500000,0x4000,0);
  _DAT_c069ea30 = FUN_c00126a4(0x1c000000,0x10000,0);
  _DAT_c069ea80 = iVar1 + 0x1c;
  DAT_c069ea51 = 0xff;
  _DAT_c069ea78 = 0;
  _DAT_c069ea7c = 0;
  _DAT_c069ea84 = iVar1 + 0x54;
  _DAT_c069ea5c = 0xf0500000;
  _DAT_c069ea60 = 0xf0400000;
  DAT_c069ea50 = 1;
  _DAT_c069ea54 = 0x20000000;
  _DAT_c069ea6c = uVar4;
  _DAT_c069ea70 = uVar5;
  _DAT_c069ea58 = FUN_c00126a4(0xf100000,0x4000,0);
  _DAT_c069ea64 = FUN_c00126a4(0x9600000,0x4000,0);
  _DAT_c069ea68 = FUN_c00126a4(0x2c000000,0x10000,0);
  FUN_c000e9c4(0,&DAT_c065e7f0);
  return 0;
}

