// module: tm.ko
// function: cla_get_hash_poly_config @ 0x111ac
// size: 308 bytes
//

undefined4 cla_get_hash_poly_config(uint *param_1)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  uint local_14;
  
  local_14 = 0;
  cVar2 = tmOnuRegRead(0xc,&local_14,0,&claRegTable);
  if (cVar2 == '\0') {
    *param_1 = local_14 & 3;
    uVar1 = g_tm_debug_level;
    param_1[6] = (local_14 << 10) >> 0x1e;
    param_1[4] = (local_14 << 0xe) >> 0x1e;
    param_1[5] = (local_14 << 0xc) >> 0x1e;
    param_1[7] = (local_14 << 8) >> 0x1e;
    param_1[3] = (local_14 << 0x18) >> 0x1e;
    param_1[2] = (local_14 << 0x1a) >> 0x1e;
    param_1[1] = (local_14 << 0x1c) >> 0x1e;
    if (((uVar1 < 7) || (printk("[TM][cla_get_hash_poly_config]output: \n"), g_tm_debug_level < 7))
       || (printk("hash0_poly = %d, hash1_poly = %d, hash2_poly = %d, hash3_poly = %d\n",*param_1,
                  param_1[1],param_1[2],param_1[3]), g_tm_debug_level < 7)) {
      return 0;
    }
    printk("ouer_hash0 = %d, ouer_hash1 = %d, ouer_hash2 = %d, ouer_hash3 = %d\n",param_1[4],
           param_1[5],param_1[6],param_1[7]);
    uVar3 = 0;
  }
  else if (g_tm_debug_level < 7) {
    uVar3 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_hash_poly_config]reg read failed\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

