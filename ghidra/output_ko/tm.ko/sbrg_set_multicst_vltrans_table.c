// module: tm.ko
// function: sbrg_set_multicst_vltrans_table @ 0x1bb80
// size: 428 bytes
//

undefined4
sbrg_set_multicst_vltrans_table(uint *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  
  uVar5 = *param_1;
  bVar9 = 3 < uVar5;
  bVar8 = uVar5 == 4;
  if (uVar5 < 5) {
    bVar9 = 0x2e < param_2;
    bVar8 = param_2 == 0x2f;
  }
  if ((((bVar9 && !bVar8) || (uVar1 = param_1[1], 0xfff < uVar1)) || (uVar6 = param_1[2], 7 < uVar6)
      ) || (((uVar3 = param_1[3], 0xfff < uVar3 || (uVar4 = param_1[4], 1 < uVar4)) ||
            (uVar7 = param_1[5], 1 < uVar7)))) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_multicst_vltrans_table]input invalid parameter!\n");
    return 1;
  }
  if (g_tm_debug_level < 7) goto LAB_0001bc08;
  printk("[TM][sbrg_set_multicst_vltrans_table]input:vlan_action = %d,multi_map = %d\n",uVar5,
         param_2,uVar5,param_4);
  if (g_tm_debug_level < 7) {
LAB_0001bd14:
    uVar3 = param_1[3];
    uVar4 = param_1[4];
  }
  else {
    printk("[TM][sbrg_set_multicst_vltrans_table]input:uni_vlan = %d,output_pt_id = %d\n",param_1[1]
           ,param_1[2]);
    uVar3 = param_1[3];
    uVar4 = param_1[4];
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_set_multicst_vltrans_table]input:pon_vlan = %d,valid = %d\n");
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_set_multicst_vltrans_table]input:en = %d\n",param_1[5]);
      }
      goto LAB_0001bd14;
    }
  }
  uVar5 = *param_1;
  uVar1 = param_1[1];
  uVar6 = param_1[2];
  uVar7 = param_1[5];
LAB_0001bc08:
  iVar2 = tmOnuRegWrite(0x48,uVar5 & 7 | uVar7 << 0x1f | (uVar1 & 0xfff) << 3 | (uVar6 & 7) << 0xf |
                             (uVar3 & 0xfff) << 0x12 | (uVar4 & 1) << 0x1e,param_2,&sbragRegTable);
  if (iVar2 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_brdmulticst_vltrans_table]write reg failed!\n");
  return 0xffffffff;
}

