// module: tm.ko
// function: sbrg_set_hash_collision_pktdeal @ 0x17f58
// size: 176 bytes
//

undefined4
sbrg_set_hash_collision_pktdeal
          (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_hash_collision_pktdeal]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_hash_collision_pktdeal]input:sel = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(6,param_1,0,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_hash_collision_pktdeal]write reg failed!\n");
  return 0xffffffff;
}

