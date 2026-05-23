// module: mt7915.ko
// function: Set_PartialScan_Timer_Interval_Proc @ 0x29fe0
// size: 540 bytes
//

uint Set_PartialScan_Timer_Interval_Proc(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  
  iVar6 = *param_1;
  if (*(int *)(iVar6 + 0x38) == 0x400 || (*(int *)(iVar6 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    uVar8 = (uint)*(byte *)(iVar6 + 0x3c);
    uVar1 = os_str_tol(param_2,0,10);
    uVar7 = *(int *)(iVar6 + 0x38) - 0x100U & 0xfffffeff;
    if (uVar7 == 0) {
      uVar2 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
      bVar9 = 0x1e < uVar8;
      if (uVar8 < 0x20) {
        bVar9 = uVar2 <= uVar8;
      }
      if (bVar9) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s(): invalid mbss id(%d)\n","Set_PartialScan_Timer_Interval_Proc",uVar8);
        return 0;
      }
      if (param_1 + uVar8 * 0x160d != (int *)0xffd48db8) {
LAB_0002a0b4:
        iVar3 = get_scan_ctrl_by_wdev(param_1);
        iVar6 = DebugLevel;
        if (DebugLevel < 1) {
          uVar7 = 1;
        }
        *(undefined4 *)(iVar3 + 0x184) = uVar1;
        if (0 < iVar6) {
          printk("Set partial scan timer interval = %d (ms)\n",uVar1);
          return 1;
        }
        return uVar7;
      }
    }
    else if (*(int *)(iVar6 + 0x38) == 0x400) {
      if (1 < uVar8) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s(): invalid apcli id(%d)\n","Set_PartialScan_Timer_Interval_Proc",uVar8);
        return 0;
      }
      if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
        piVar4 = param_1 + 0xadc92;
        piVar5 = (int *)0x0;
        do {
          if ((short)piVar4[6] == (short)param_1[uVar8 * 0x84dec + 0xdb6dc]) {
            piVar5 = piVar4;
          }
          piVar4 = piVar4 + 0x160d;
        } while (piVar4 != param_1 + (uint)(byte)(*(char *)((int)param_1 + 0x2b7242) - 1) * 0x160d +
                                     0xaf29f);
        if (piVar5 != (int *)0x0) goto LAB_0002a0b4;
      }
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s(): cannot find ap wdev based on apcli wdev phymode.",
             "Set_PartialScan_Timer_Interval_Proc");
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s(): do not support apcli, please use ap interface to set partial scan timer interval\n"
             ,"Set_PartialScan_Timer_Interval_Proc");
      return 0;
    }
  }
  return 0;
}

