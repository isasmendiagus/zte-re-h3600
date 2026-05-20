// module: tm.ko
// function: sbrg_set_pt_macaddr_clr @ 0x17a68
// size: 216 bytes
//

undefined4 sbrg_set_pt_macaddr_clr(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_2 != 0;
  bVar2 = param_2 == 1;
  if (param_2 < 2) {
    bVar3 = 0xfe < param_1;
    bVar2 = param_1 == 0xff;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_pt_macaddr_clr]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_pt_macaddr_clr]input:port_mask = 0x%x,en = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(2,param_1,0,&sbragRegTable);
  if ((iVar1 == 0) && (iVar1 = tmOnuRegWrite(3,param_2,0,&sbragRegTable), iVar1 == 0)) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][sbrg_set_pt_macaddr_clr]write reg failed!\n");
  }
  return 0xffffffff;
}

