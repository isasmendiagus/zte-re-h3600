// module: tm.ko
// function: sbrg_set_multicst_pritrans_table @ 0x1c088
// size: 340 bytes
//

undefined4 sbrg_set_multicst_pritrans_table(uint *param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  
  uVar7 = *param_1;
  bVar9 = uVar7 != 0;
  bVar8 = uVar7 == 1;
  if (uVar7 < 2) {
    bVar9 = 0x2e < param_2;
    bVar8 = param_2 == 0x2f;
  }
  if ((((bVar9 && !bVar8) || (uVar3 = param_1[1], 1 < uVar3)) ||
      (uVar5 = (uint)(byte)param_1[2], 7 < uVar5)) ||
     (uVar6 = (uint)*(byte *)((int)param_1 + 9), 7 < uVar6)) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_multicst_pritrans_table]input invalid parameter!\n");
    return 1;
  }
  if (g_tm_debug_level < 7) goto LAB_0001c0f8;
  printk("[TM][sbrg_set_multicst_pritrans_table]input:pri_en = %d,multi_map = %d\n",uVar7,param_2);
  if (g_tm_debug_level < 7) {
LAB_0001c1c8:
    bVar1 = *(byte *)((int)param_1 + 9);
    bVar2 = (byte)param_1[2];
  }
  else {
    printk("[TM][sbrg_set_multicst_pritrans_table]input:pri_use = %d\n",param_1[1]);
    bVar2 = (byte)param_1[2];
    bVar1 = *(byte *)((int)param_1 + 9);
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_set_multicst_pritrans_table]input:pon_pri = %d,uni_pri = %d\n");
      goto LAB_0001c1c8;
    }
  }
  uVar6 = (uint)bVar1;
  uVar5 = (uint)bVar2;
  uVar7 = *param_1;
  uVar3 = param_1[1];
LAB_0001c0f8:
  iVar4 = tmOnuRegWrite(0x4a,(uVar7 & 1) << 7 | (uVar3 & 1) << 3 | uVar6 & 7 | (uVar5 & 7) << 4,
                        param_2,&sbragRegTable);
  if (iVar4 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_multicst_pritrans_table]write reg failed!\n");
  return 0xffffffff;
}

