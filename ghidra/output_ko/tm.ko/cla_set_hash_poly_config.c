// module: tm.ko
// function: cla_set_hash_poly_config @ 0x1103c
// size: 368 bytes
//

undefined4 cla_set_hash_poly_config(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (((6 < g_tm_debug_level) &&
      (printk("[TM][cla_set_hash_poly_config]input:\n"), 6 < g_tm_debug_level)) &&
     (printk("hash0_poly = %d, hash1_poly = %d, hash2_poly = %d, hash3_poly = %d\n",*param_1,
             param_1[1],param_1[2],param_1[3]), 6 < g_tm_debug_level)) {
    printk("ouer_hash0 = %d, ouer_hash1 = %d, ouer_hash2 = %d, ouer_hash3 = %d\n",param_1[4],
           param_1[5],param_1[6],param_1[7]);
  }
  if (((((param_1[3] < 4) && (param_1[2] < 4)) &&
       ((param_1[1] < 4 && ((*param_1 < 4 && (param_1[7] < 4)))))) && (param_1[6] < 4)) &&
     ((param_1[5] < 4 && (param_1[4] < 4)))) {
    iVar2 = tmOnuRegWrite(0xc,param_1[6] * 0x100000 + param_1[7] * 0x400000 + *param_1 +
                              param_1[5] * 0x40000 + param_1[4] * 0x10000 + param_1[3] * 0x40 +
                              param_1[2] * 0x10 + param_1[1] * 4,0,&claRegTable);
    uVar1 = 0;
    if (iVar2 != 0) {
      if (g_tm_debug_level == 0) {
        uVar1 = 0xffffffff;
      }
      else {
        printk("[TM][cla_set_hash_poly_config]reg write failed\n");
        uVar1 = 0xffffffff;
      }
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_set_hash_poly_config]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

