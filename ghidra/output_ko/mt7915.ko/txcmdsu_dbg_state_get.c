// module: mt7915.ko
// function: txcmdsu_dbg_state_get @ 0x28e2ac
// size: 1524 bytes
//

undefined4 txcmdsu_dbg_state_get(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  byte *local_110;
  undefined4 local_10c;
  byte local_108;
  byte local_107 [7];
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68 [16];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  ushort local_14;
  
  pbVar6 = &local_108;
  printk(&_LC4,"TXCMDSU","txcmdsu_dbg_state_get");
  printk(&_LC5,"TXCMDSU","txcmdsu_dbg_state_get",param_3);
  local_124 = 0x1a;
  local_120 = 200;
  local_118 = 0xf8;
  local_11c = 0;
  local_114 = 0;
  local_10c = 0;
  local_110 = pbVar6;
  iVar4 = dbg_ut_wmcu_send(param_1,&local_124);
  if (iVar4 != 0) {
    printk(&_LC6,"TXCMDSU","txcmdsu_dbg_state_get");
  }
  printk(&_LC7,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC8,"TXCMDSU","txcmdsu_dbg_state_dump",local_108);
  iVar4 = 0;
  pbVar8 = pbVar6;
  do {
    pbVar8 = pbVar8 + 1;
    uVar5 = (uint)*pbVar8;
    iVar7 = iVar4 + 1;
    printk(&_LC9,"TXCMDSU","txcmdsu_dbg_state_dump",iVar4,uVar5);
    iVar4 = iVar7;
  } while (iVar7 != 4);
  printk(&_LC10,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC11,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC12,"TXCMDSU","txcmdsu_dbg_state_dump",local_74,uVar5);
  printk(&_LC13,"TXCMDSU","txcmdsu_dbg_state_dump",local_70);
  printk(&_LC14,"TXCMDSU","txcmdsu_dbg_state_dump",local_6c);
  printk(&_LC15,"TXCMDSU","txcmdsu_dbg_state_dump");
  iVar4 = 0;
  do {
    pbVar8 = pbVar6 + 0xa0;
    pbVar1 = pbVar6 + 0xac;
    pbVar2 = pbVar6 + 0xa4;
    pbVar3 = pbVar6 + 0xa8;
    iVar7 = iVar4 + 1;
    pbVar6 = pbVar6 + 0x10;
    printk(&_LC16,"TXCMDSU","txcmdsu_dbg_state_dump",iVar4,*(undefined4 *)pbVar8,
           *(undefined4 *)pbVar2,*(undefined4 *)pbVar3,*(undefined4 *)pbVar1);
    iVar4 = iVar7;
  } while (iVar7 != 4);
  printk(&_LC17,"TXCMDSU","txcmdsu_dbg_state_dump",local_28,local_24,local_20,local_1c,local_18);
  printk(&_LC18,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC19,"TXCMDSU","txcmdsu_dbg_state_dump",local_ec);
  printk(&_LC20,"TXCMDSU","txcmdsu_dbg_state_dump",local_e4);
  printk(&_LC21,"TXCMDSU","txcmdsu_dbg_state_dump",local_dc);
  printk(&_LC22,"TXCMDSU","txcmdsu_dbg_state_dump",local_f0);
  printk(&_LC23,"TXCMDSU","txcmdsu_dbg_state_dump",local_e0);
  printk(&_LC24,"TXCMDSU","txcmdsu_dbg_state_dump",local_e8);
  printk(&_LC25,"TXCMDSU","txcmdsu_dbg_state_dump",local_d8);
  printk(&_LC26,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC19,"TXCMDSU","txcmdsu_dbg_state_dump",local_d0);
  printk(&_LC20,"TXCMDSU","txcmdsu_dbg_state_dump",local_c8);
  printk(&_LC21,"TXCMDSU","txcmdsu_dbg_state_dump",local_c0);
  printk(&_LC22,"TXCMDSU","txcmdsu_dbg_state_dump",local_d4);
  printk(&_LC23,"TXCMDSU","txcmdsu_dbg_state_dump",local_c4);
  printk(&_LC24,"TXCMDSU","txcmdsu_dbg_state_dump",local_cc);
  printk(&_LC25,"TXCMDSU","txcmdsu_dbg_state_dump",local_bc);
  printk(&_LC27,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC28,"TXCMDSU","txcmdsu_dbg_state_dump",local_f4);
  printk(&_LC29,"TXCMDSU","txcmdsu_dbg_state_dump",local_fc);
  printk(&_LC30,"TXCMDSU","txcmdsu_dbg_state_dump",local_f8);
  printk(&_LC31,"TXCMDSU","txcmdsu_dbg_state_dump",local_100);
  printk(&_LC32,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC33,"TXCMDSU","txcmdsu_dbg_state_dump",local_b8);
  printk(&_LC34,"TXCMDSU","txcmdsu_dbg_state_dump",local_b4);
  printk(&_LC35,"TXCMDSU","txcmdsu_dbg_state_dump",local_b0);
  printk(&_LC36,"TXCMDSU","txcmdsu_dbg_state_dump",local_ac);
  printk(&_LC37,"TXCMDSU","txcmdsu_dbg_state_dump",local_a8);
  printk(&_LC38,"TXCMDSU","txcmdsu_dbg_state_dump",local_a4);
  printk(&_LC39,"TXCMDSU","txcmdsu_dbg_state_dump",local_98);
  printk(&_LC40,"TXCMDSU","txcmdsu_dbg_state_dump",local_94);
  printk(&_LC41,"TXCMDSU","txcmdsu_dbg_state_dump");
  printk(&_LC42,"TXCMDSU","txcmdsu_dbg_state_dump",((uint)(byte)local_14 << 0x1b) >> 0x1e);
  printk(&_LC43,"TXCMDSU","txcmdsu_dbg_state_dump",((uint)local_14 << 0x17) >> 0x1d);
  printk(&_LC44,"TXCMDSU","txcmdsu_dbg_state_dump",((uint)(byte)local_14 << 0x1a) >> 0x1f);
  return 0;
}

