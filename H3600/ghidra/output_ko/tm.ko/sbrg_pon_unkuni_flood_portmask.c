// module: tm.ko
// function: sbrg_pon_unkuni_flood_portmask @ 0x21724
// size: 176 bytes
//

undefined4
sbrg_pon_unkuni_flood_portmask
          (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if ((param_1 & 1) != 0) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_pon_unkuni_flood_portmask]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_pon_unkuni_flood_portmask]input:port_mask = 0x%x\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(0x37,param_1,0,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_pon_unkuni_flood_portmask]write reg failed!\n");
  return 0xffffffff;
}

