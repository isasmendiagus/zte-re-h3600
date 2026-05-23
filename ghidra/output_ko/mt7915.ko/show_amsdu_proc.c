// module: mt7915.ko
// function: show_amsdu_proc @ 0xe0d74
// size: 572 bytes
//

undefined4 show_amsdu_proc(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  bool bVar12;
  undefined4 *local_40;
  uint local_3c;
  undefined4 *local_38;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(param_1 + 0x9daa0) == '\0') {
    if ((0 < DebugLevel) && (printk("TX AMSDU Usage\n"), 0 < DebugLevel)) {
      printk(
            "\tTimeSlot \tamsdu_1 \tamsdu_2 \tamsdu_3 \tamsdu_4\t\t\t\t\t\t\t\t\t\tamsdu_5\t amsdu_6\t amsdu_7\t amsdu_8\n"
            );
    }
    local_38 = (undefined4 *)(param_1 + 0xa2a2c);
    local_40 = (undefined4 *)(param_1 + 0x2fb5c);
    local_3c = 0;
    while( true ) {
      uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      bVar12 = 0x11f < local_3c;
      if (local_3c != 0x120) {
        bVar12 = uVar2 <= local_3c;
      }
      if (bVar12) break;
      if (local_40[-0x12f] != 0) {
        if (0 < DebugLevel) {
          printk("\ttr_entry index = %d, amsdu_limit_len_adjust = %d\n",local_3c,*local_38);
        }
        iVar1 = 0;
        puVar11 = local_40 + 0xb;
        puVar10 = local_40 + 0x16;
        puVar9 = local_40 + 0x21;
        puVar8 = local_40 + 0x2c;
        puVar7 = local_40 + 0x37;
        puVar6 = local_40 + 0x42;
        puVar5 = local_40 + 0x4d;
        puVar4 = local_40;
        do {
          if (0 < DebugLevel) {
            printk("\t%d \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d \t\t%d\n"
                   ,iVar1,*puVar4,*puVar11,*puVar10,*puVar9,*puVar8,*puVar7,*puVar6,*puVar5);
          }
          iVar1 = iVar1 + 1;
          puVar4 = puVar4 + 1;
          puVar11 = puVar11 + 1;
          puVar10 = puVar10 + 1;
          puVar9 = puVar9 + 1;
          puVar8 = puVar8 + 1;
          puVar7 = puVar7 + 1;
          puVar6 = puVar6 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar1 != 10);
      }
      local_3c = local_3c + 1;
      local_40 = local_40 + 0x188;
      local_38 = local_38 + 0x530;
    }
  }
  else if (*(char *)(param_1 + 0x9daa0) == '\x01') {
    if (*(code **)(iVar1 + 0x50) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e0f08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar3 = (**(code **)(iVar1 + 0x50))(*(undefined4 *)(param_1 + 0xa797a0));
      return uVar3;
    }
    uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar2 & 0x1000) != 0) {
      asic_dump_dmac_amsdu_info(param_1);
    }
  }
  return 1;
}

