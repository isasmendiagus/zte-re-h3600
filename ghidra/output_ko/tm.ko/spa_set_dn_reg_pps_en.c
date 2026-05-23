// module: tm.ko
// function: spa_set_dn_reg_pps_en @ 0x388d4
// size: 284 bytes
//

uint spa_set_dn_reg_pps_en(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  uint local_1c [2];
  
  bVar4 = 0x3e < param_1;
  bVar3 = param_1 == 0x3f;
  if (param_1 < 0x40) {
    bVar4 = param_2 != 0;
    bVar3 = param_2 == 1;
  }
  local_1c[0] = 0;
  if (!bVar4 || bVar3) {
    if (param_1 < 0x20) {
      uVar1 = tmOnuRegRead(3,local_1c,bVar4 && !bVar3,&spaRegTable);
      uVar2 = tmOnuRegWrite(3,local_1c[0] & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff),
                            bVar4 && !bVar3,&spaRegTable);
      uVar2 = uVar2 | uVar1;
    }
    else {
      uVar1 = tmOnuRegRead(3,local_1c,1,&spaRegTable);
      uVar2 = tmOnuRegWrite(3,local_1c[0] & ~(1 << (param_1 - 0x20 & 0xff)) |
                              param_2 << (param_1 - 0x20 & 0xff),1,&spaRegTable);
      uVar2 = uVar2 | uVar1;
    }
    if ((uVar2 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_dn_reg_pps_en]write reg failed!\n");
    }
    return uVar2;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][spa_set_dn_reg_pps_en] input invalid parameter!\n");
  }
  return 1;
}

