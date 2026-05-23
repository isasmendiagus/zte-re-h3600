// FUN_c000e9c4 @ c000e9c4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_c000e9c4(undefined4 param_1,undefined4 *param_2)

{
  int ****ppppiVar1;
  int ****ppppiVar2;
  int iVar3;
  int ***extraout_r2;
  int ***extraout_r2_00;
  int ***pppiVar4;
  int ****ppppiVar5;
  int ****ppppiVar6;
  int iVar7;
  int ***pppiVar8;
  int ***pppiVar9;
  int ***local_3c;
  int ***local_30;
  int ***local_2c;
  
  _DAT_c06abdf4 = _DAT_c06abdf4 | 1;
  local_30 = (int ***)&local_30;
  local_2c = (int ***)&local_30;
  if ((code *)param_2[5] != (code *)0x0) {
    (*(code *)param_2[5])();
  }
  if (0 < (int)param_2[1]) {
    pppiVar9 = (int ***)0x0;
    iVar7 = 0;
    pppiVar8 = (int ***)0x0;
    local_3c = (int ***)&DAT_c067694c;
    do {
      ppppiVar2 = (int ****)FUN_c00a2ff0(_DAT_c06a7128,0x80d0);
      if (ppppiVar2 == (int ****)0x0) {
                    /* WARNING: Subroutine does not return */
        FUN_c046a900(s_PCI__unable_to_allocate_sys_data_c05839ac);
      }
      ppppiVar2[2] = pppiVar8;
      ppppiVar6 = ppppiVar2 + 8;
      ppppiVar2[0x14] = (int ***)param_2[7];
      ppppiVar2[0x15] = (int ***)param_2[8];
      pppiVar4 = (int ***)param_2[9];
      ppppiVar2[8] = (int ***)ppppiVar6;
      ppppiVar2[9] = (int ***)ppppiVar6;
      ppppiVar2[0x16] = pppiVar4;
      if (param_2[2] != 0) {
        ppppiVar2[0x17] = *(int ****)(param_2[2] + iVar7 * 4);
      }
      iVar3 = (*(code *)param_2[3])(iVar7,ppppiVar2);
      if (iVar3 < 1) {
        FUN_c00a35dc(ppppiVar2);
        if (iVar3 != 0) break;
      }
      else {
        ppppiVar5 = (int ****)ppppiVar2[8];
        pppiVar8 = extraout_r2;
        if (ppppiVar6 == ppppiVar5) {
          FUN_c01b2afc(ppppiVar6,&DAT_c0680210,ppppiVar2[4]);
          ppppiVar5 = (int ****)ppppiVar2[8];
          pppiVar8 = extraout_r2_00;
        }
        for (; ppppiVar6 != ppppiVar5; ppppiVar5 = (int ****)*ppppiVar5) {
          pppiVar8 = (int ***)((uint)ppppiVar5[2][3] & 0x1f00);
          if (pppiVar8 == (int ***)0x100) goto LAB_c000eb38;
        }
        ppppiVar1 = (int ****)local_3c;
        if (pppiVar9 != (int ***)0x0) {
          pppiVar8 = pppiVar9;
          ppppiVar1 = ppppiVar5;
        }
        ppppiVar2[0xc] = (int ***)(ppppiVar2 + 0x11);
        if (pppiVar9 == (int ***)0x0) {
          pppiVar8 = *ppppiVar1;
        }
        ppppiVar2[0xb] = (int ***)((int)pppiVar9 + 0xffff);
        ppppiVar2[0xd] = (int ***)0x100;
        ppppiVar2[10] = pppiVar8;
        FUN_c018b83c(ppppiVar2 + 0x11,s_PCI_d_I_O_c05839d0,iVar7);
        iVar3 = FUN_c001db98(&DAT_c068022c,ppppiVar2 + 10);
        if (iVar3 != 0) {
          FUN_c046ab98(&DAT_c05839dc,iVar3);
          FUN_c00a35dc(ppppiVar2);
          break;
        }
        FUN_c01b2afc(ppppiVar6,ppppiVar2 + 10,ppppiVar2[6]);
LAB_c000eb38:
        if ((code *)param_2[4] == (code *)0x0) {
          pppiVar8 = (int ***)FUN_c01b59b4(param_1,ppppiVar2[2],*param_2,ppppiVar2,ppppiVar6);
          ppppiVar2[7] = pppiVar8;
        }
        else {
          pppiVar8 = (int ***)(*(code *)param_2[4])(iVar7,ppppiVar2);
          ppppiVar2[7] = pppiVar8;
        }
        if (pppiVar8 == (int ***)0x0) {
                    /* WARNING: Subroutine does not return */
          FUN_c046a900(s_PCI__unable_to_scan_bus__c0583a0c);
        }
        pppiVar8 = (int ***)((int)pppiVar8[0x11] + 1);
        local_30[1] = (int **)ppppiVar2;
        *ppppiVar2 = local_30;
        ppppiVar2[1] = (int ***)&local_30;
        local_30 = (int ***)ppppiVar2;
      }
      iVar7 = iVar7 + 1;
      pppiVar9 = pppiVar9 + 0x4000;
    } while (iVar7 < (int)param_2[1]);
  }
  if ((code *)param_2[6] != (code *)0x0) {
    (*(code *)param_2[6])();
  }
  FUN_c01c6e98(FUN_c000e838,FUN_c000e29c);
  ppppiVar2 = (int ****)local_30;
  if ((int ****)local_30 != &local_30) {
    do {
      pppiVar8 = ppppiVar2[7];
      if ((_DAT_c06abdf4 & 4) == 0) {
        FUN_c01bfe04(pppiVar8);
        FUN_c01bff08(pppiVar8);
      }
      FUN_c01b2cc4(pppiVar8);
      ppppiVar2 = (int ****)*ppppiVar2;
      ppppiVar6 = (int ****)local_30;
    } while (ppppiVar2 != &local_30);
    for (; ppppiVar6 != &local_30; ppppiVar6 = (int ****)*ppppiVar6) {
      if ((ppppiVar6[7] != (int ***)0x0) && ((_DAT_c06abdf4 & 4) == 0)) {
        pppiVar9 = ppppiVar6[7] + 3;
        for (pppiVar8 = (int ***)*pppiVar9; pppiVar8 != pppiVar9; pppiVar8 = (int ***)*pppiVar8) {
          FUN_c01b3c74(pppiVar8);
        }
      }
    }
  }
  return;
}

