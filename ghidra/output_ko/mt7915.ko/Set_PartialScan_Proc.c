// module: mt7915.ko
// function: Set_PartialScan_Proc @ 0x29d68
// size: 628 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 Set_PartialScan_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  
  iVar6 = *param_1;
  if (*(int *)(iVar6 + 0x38) != 0x400 && (*(int *)(iVar6 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  uVar7 = (uint)*(byte *)(iVar6 + 0x3c);
  cVar2 = os_str_tol(param_2,0,10);
  if ((*(int *)(iVar6 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    uVar3 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    bVar8 = 0x1e < uVar7;
    if (uVar7 < 0x20) {
      bVar8 = uVar3 <= uVar7;
    }
    if (bVar8) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s(): invalid mbss id(%d)\n","Set_PartialScan_Proc",uVar7);
      return 0;
    }
    piVar5 = param_1 + uVar7 * 0x160d + 0xadc92;
    if (piVar5 != (int *)0x0) {
LAB_00029e3c:
      iVar6 = get_scan_ctrl_by_wdev(param_1,piVar5);
      if (cVar2 != '\0') {
        if (*(char *)(iVar6 + 0x17c) != '\0') {
          if (DebugLevel < 1) {
            return 0;
          }
          printk("%s(): partial scan is under process is under process. cannot trigger new partial scan\n"
                 ,"Set_PartialScan_Proc");
          return 0;
        }
        *(int **)(iVar6 + 0x1bc) = piVar5;
        *(undefined1 *)((int)piVar5 + 0xbb6) = 0;
      }
      iVar1 = DebugLevel;
      *(bool *)(iVar6 + 0x17c) = cVar2 != '\0';
      if (iVar1 < 1) {
        return 1;
      }
      printk("%s(): bScanning = %u\n","Set_PartialScan_Proc");
      return 1;
    }
  }
  else if (*(int *)(iVar6 + 0x38) == 0x400) {
    if (1 < uVar7) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s(): invalid apcli id(%d)\n","Set_PartialScan_Proc",uVar7);
      return 0;
    }
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      piVar4 = param_1 + 0xadc92;
      piVar5 = (int *)0x0;
      do {
        if ((short)piVar4[6] == (short)param_1[uVar7 * 0x84dec + 0xdb6dc]) {
          piVar5 = piVar4;
        }
        piVar4 = piVar4 + 0x160d;
      } while (piVar4 != param_1 + (uint)(byte)(*(char *)((int)param_1 + 0x2b7242) - 1) * 0x160d +
                                   0xaf29f);
      if (piVar5 != (int *)0x0) goto LAB_00029e3c;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): cannot find ap wdev based on apcli wdev phymode\n","Set_PartialScan_Proc");
    return 0;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s(): do not support apcli, please use ap interface to trigger partial scan\n",
         "Set_PartialScan_Proc");
  return 0;
}

