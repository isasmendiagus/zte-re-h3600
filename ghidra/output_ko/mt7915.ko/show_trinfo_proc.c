// module: mt7915.ko
// function: show_trinfo_proc @ 0xe2954
// size: 1484 bytes
//

undefined4 show_trinfo_proc(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  int ***pppiVar10;
  char *pcVar11;
  int ***pppiVar12;
  uint uVar13;
  uint *puVar14;
  int iVar15;
  undefined4 *puVar16;
  uint uVar17;
  int ****ppppiVar18;
  int ****ppppiVar19;
  uint auStack_78 [6];
  int ***local_60 [2];
  int local_58;
  int local_54;
  undefined1 *local_50;
  uint *local_4c;
  int local_48;
  int local_44;
  int ***local_40;
  int local_3c;
  int *local_38;
  uint *local_34;
  int local_30;
  uint local_2c;
  
  local_48 = param_1 + 0xa70000;
  local_44 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  local_2c = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  local_30 = hif_get_rx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("=================================================\n");
  }
  uVar17 = local_2c;
  if ((*(int *)(param_1 + 0x286280) - 4U < 2) || (*(int *)(param_1 + 0x286280) == 1)) {
    uVar9 = (short)local_30 * 4 + 10U & 0xfffffff8;
    uVar4 = (short)local_2c * 4 + 10U & 0xfffffff8;
    iVar7 = uVar4 * -4;
    local_54 = (int)local_60 - uVar4;
    local_34 = (uint *)((int)local_60 + uVar4 * -2);
    local_38 = (int *)((int)local_60 + uVar4 * -3);
    ppppiVar18 = local_60 + -uVar4;
    local_58 = (int)local_60 + (iVar7 - uVar9);
    local_4c = (uint *)((int)local_60 + uVar9 * -2 + iVar7);
    local_3c = (int)local_60 + uVar9 * -3 + iVar7;
    local_40 = (int ***)(local_60 + (-uVar4 - uVar9));
    local_50 = (undefined1 *)auStack_78;
    iVar2 = IsStopingPdma(param_1 + 0xa7bf04);
    iVar7 = local_54;
    if (iVar2 != 0) {
      return 1;
    }
    ppppiVar19 = (int ****)&DebugLevel;
    if (uVar17 != 0) {
      local_60[1] = (int ***)&DebugLevel;
      iVar2 = 0;
      uVar17 = 0;
      do {
        uVar17 = uVar17 + 1;
        iVar15 = *(int *)(*(int *)(iVar1 + 8) + iVar2);
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 0x2c),
                      iVar7 + iVar2);
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 0x30),
                      (undefined *)((int)local_34 + iVar2));
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 0x24),
                      (int)local_38 + iVar2);
        iVar5 = (int)ppppiVar18 + iVar2;
        iVar2 = iVar2 + 4;
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 4),iVar5);
        ppppiVar19 = (int ****)local_60[1];
      } while (local_2c != uVar17);
    }
    puVar14 = local_4c;
    iVar7 = local_58;
    if (local_30 != 0) {
      iVar2 = 0;
      iVar5 = 0;
      local_60[0] = (int ***)ppppiVar19;
      local_60[1] = (int ***)ppppiVar18;
      do {
        iVar5 = iVar5 + 1;
        iVar15 = *(int *)(*(int *)(iVar1 + 4) + iVar2);
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 0x4c),
                      iVar7 + iVar2);
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 0x50),
                      (int)puVar14 + iVar2);
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 0x3c),
                      local_3c + iVar2);
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar15 + 8),
                      (int)local_40 + iVar2);
        iVar2 = iVar2 + 4;
        ppppiVar18 = (int ****)local_60[1];
        ppppiVar19 = (int ****)local_60[0];
      } while (local_30 != iVar5);
    }
    if ((0 < (int)*ppppiVar19) && (printk("TxRing Configuration\n"), 0 < DebugLevel)) {
      auStack_78[-uVar4 - uVar9] = (uint)&_LC576;
      auStack_78[(1 - uVar9) - uVar4] = (uint)&_LC577;
      auStack_78[(2 - uVar9) - uVar4] = (uint)&_LC578;
      auStack_78[(3 - uVar9) - uVar4] = (uint)&_LC579;
      auStack_78[(4 - uVar9) - uVar4] = (uint)&_LC580;
      auStack_78[(5 - uVar9) - uVar4] = (uint)"FreeCnt";
      printk("%4s %8s %8s %10s %6s %6s %6s %6s %6s\n",&_LC573,&_LC574,&_LC575);
    }
    puVar14 = local_34;
    if (local_2c != 0) {
      ppppiVar18 = ppppiVar18 + -1;
      uVar17 = 0;
      puVar8 = (uint *)(local_38 + -1);
      local_34 = (uint *)(param_1 + 0xa79000);
      do {
        puVar8 = puVar8 + 1;
        pppiVar10 = (int ***)*puVar8;
        ppppiVar18 = ppppiVar18 + 1;
        pppiVar12 = *ppppiVar18;
        local_38 = *(int **)(*(int *)(iVar1 + 8) + uVar17 * 4);
        uVar13 = (int)pppiVar10 - (int)pppiVar12;
        piVar6 = local_38;
        if (pppiVar10 < pppiVar12) {
          piVar6 = (int *)*puVar14;
        }
        if (pppiVar10 < pppiVar12) {
          uVar13 = uVar13 + (int)piVar6;
        }
        uVar3 = hif_get_tx_resource_free_num(local_34[0x1e8],uVar17 & 0xff);
        if (0 < (int)*ppppiVar19) {
          iVar7 = *local_38;
          if (iVar7 == 0) {
            pcVar11 = "DATA";
          }
          else if (iVar7 == 1) {
            pcVar11 = "CMD";
          }
          else if (iVar7 == 2) {
            pcVar11 = "CMD_WM";
          }
          else {
            pcVar11 = "FWDL";
            if (iVar7 != 3) {
              pcVar11 = "UN";
            }
          }
          iVar7 = local_38[0xb];
          auStack_78[-uVar4 - uVar9] = *(undefined4 *)(local_54 + uVar17 * 4);
          auStack_78[(1 - uVar9) - uVar4] = *puVar14;
          auStack_78[(2 - uVar9) - uVar4] = *puVar8;
          pppiVar10 = *ppppiVar18;
          auStack_78[(4 - uVar9) - uVar4] = uVar13;
          auStack_78[(5 - uVar9) - uVar4] = uVar3;
          auStack_78[(3 - uVar9) - uVar4] = (uint)pppiVar10;
          printk("%4d %8s %8x %10x %6x %6x %6x %6x %6x\n",uVar17,pcVar11,iVar7);
        }
        uVar17 = uVar17 + 1;
        puVar14 = puVar14 + 1;
      } while (local_2c != uVar17);
    }
    if ((0 < (int)*ppppiVar19) && (printk("RxRing Configuration\n"), 0 < DebugLevel)) {
      auStack_78[-uVar4 - uVar9] = (uint)&_LC576;
      auStack_78[(1 - uVar9) - uVar4] = (uint)&_LC577;
      auStack_78[(2 - uVar9) - uVar4] = (uint)&_LC578;
      auStack_78[(3 - uVar9) - uVar4] = (uint)&_LC579;
      auStack_78[(4 - uVar9) - uVar4] = (uint)&_LC580;
      printk("%4s %8s %8s %10s %6s %6s %6s %6s\n",&_LC573,&_LC574,&_LC575);
    }
    iVar7 = local_30;
    if (local_30 != 0) {
      ppppiVar18 = (int ****)(local_40 + -1);
      local_34 = (uint *)0x2d8adc;
      iVar2 = 0;
      puVar16 = (undefined4 *)(local_3c + -4);
      puVar14 = local_4c;
      do {
        ppppiVar18 = ppppiVar18 + 1;
        pppiVar10 = *ppppiVar18;
        puVar16 = puVar16 + 1;
        pppiVar12 = (int ***)*puVar16;
        uVar17 = (int)pppiVar10 - 1;
        local_2c = uVar17 - (int)pppiVar12;
        if (pppiVar10 <= pppiVar12) {
          uVar17 = *puVar14;
        }
        piVar6 = *(int **)(*(int *)(iVar1 + 4) + iVar2 * 4);
        if (pppiVar10 <= pppiVar12) {
          local_2c = local_2c + uVar17;
        }
        if (0 < (int)*ppppiVar19) {
          iVar5 = *piVar6;
          if (iVar5 == 4) {
            puVar8 = (uint *)&_LC565;
          }
          else {
            puVar8 = (uint *)&_LC567;
            if (iVar5 == 5) {
              puVar8 = local_34;
            }
          }
          iVar5 = piVar6[0x13];
          auStack_78[-uVar4 - uVar9] = *(undefined4 *)(local_58 + iVar2 * 4);
          uVar17 = *puVar14;
          auStack_78[(3 - uVar9) - uVar4] = (uint)pppiVar10;
          auStack_78[(1 - uVar9) - uVar4] = uVar17;
          auStack_78[(2 - uVar9) - uVar4] = (uint)pppiVar12;
          auStack_78[(4 - uVar9) - uVar4] = local_2c;
          printk("%4d %8s %8x %10x %6x %6x %6x %6x\n",iVar2,puVar8,iVar5);
        }
        iVar2 = iVar2 + 1;
        puVar14 = puVar14 + 1;
      } while (iVar7 != iVar2);
    }
  }
  if (*(code **)(local_44 + 0x5c) != (code *)0x0) {
    (**(code **)(local_44 + 0x5c))(*(undefined4 *)(local_48 + 0x97a0));
  }
  return 1;
}

