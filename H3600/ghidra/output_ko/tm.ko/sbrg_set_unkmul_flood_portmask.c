// module: tm.ko
// function: sbrg_set_unkmul_flood_portmask @ 0x21598
// size: 220 bytes
//

undefined4 sbrg_set_unkmul_flood_portmask(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  
  bVar4 = 0xfe < param_2;
  bVar3 = param_2 == 0xff;
  if (param_2 < 0x100) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  if (!bVar4 || bVar3) {
    if (param_1 == 1) {
      uVar1 = param_2 & 2;
    }
    else {
      if (param_1 != 0) goto LAB_000215ec;
      uVar1 = param_2 & 1;
    }
    if (uVar1 == 0) {
LAB_000215ec:
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_set_unkmul_flood_portmask]input:port_mask = 0x%x,port_id = %d\n",param_2,
               param_1);
      }
      iVar2 = tmOnuRegWrite(0x30,param_2,param_1,&sbragRegTable);
      if (iVar2 != 0) {
        if (g_tm_debug_level != 0) {
          printk("[TM][sbrg_set_unkmul_flood_portmask]write reg failed!\n");
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      return 0;
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][sbrg_set_unkmul_flood_portmask]input invalid parameter!\n");
    return 1;
  }
  return 1;
}

