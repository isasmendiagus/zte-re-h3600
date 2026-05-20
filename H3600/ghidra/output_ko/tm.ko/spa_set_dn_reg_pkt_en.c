// module: tm.ko
// function: spa_set_dn_reg_pkt_en @ 0x38640
// size: 376 bytes
//

uint spa_set_dn_reg_pkt_en(uint param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  uint local_1c [2];
  
  bVar5 = 0x51 < param_1;
  bVar4 = param_1 == 0x52;
  if (param_1 < 0x53) {
    bVar5 = param_2 != 0;
    bVar4 = param_2 == 1;
  }
  bVar1 = bVar5 && !bVar4;
  local_1c[0] = 0;
  if (!bVar5 || bVar4) {
    if (param_1 < 0x20) {
      uVar2 = tmOnuRegRead(1,local_1c,bVar1,&spaRegTable);
      uVar3 = tmOnuRegWrite(1,local_1c[0] & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff),
                            bVar1,&spaRegTable);
      uVar3 = uVar3 | uVar2;
    }
    else if (param_1 < 0x40) {
      uVar2 = tmOnuRegRead(1,local_1c,1,&spaRegTable);
      uVar3 = tmOnuRegWrite(1,local_1c[0] & ~(1 << (param_1 - 0x20 & 0xff)) |
                              param_2 << (param_1 - 0x20 & 0xff),1,&spaRegTable);
      uVar3 = uVar3 | uVar2;
    }
    else {
      uVar2 = tmOnuRegRead(1,local_1c,bVar1,&spaRegTable);
      uVar3 = tmOnuRegWrite(1,local_1c[0] & ~(1 << (param_1 - 0x40 & 0xff)) |
                              param_2 << (param_1 - 0x40 & 0xff),bVar1,&spaRegTable);
      uVar3 = uVar3 | uVar2;
    }
    if ((uVar3 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_dn_reg_pkt_en]write reg failed!\n");
    }
    return uVar3;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][spa_set_dn_reg_pkt_en] input invalid parameter!\n");
  }
  return 1;
}

