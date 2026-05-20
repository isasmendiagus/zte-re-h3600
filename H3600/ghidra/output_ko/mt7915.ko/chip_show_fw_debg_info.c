// module: mt7915.ko
// function: chip_show_fw_debg_info @ 0x193da0
// size: 4024 bytes
//

undefined4 chip_show_fw_debg_info(int param_1)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  undefined **ppuVar14;
  undefined4 uVar15;
  int iVar16;
  undefined4 uVar17;
  uint uVar18;
  uint uVar19;
  char *pcVar20;
  undefined **ppuVar21;
  undefined4 uVar22;
  undefined **ppuVar23;
  undefined4 uVar24;
  uint uVar25;
  int iVar26;
  undefined **ppuVar27;
  undefined4 uVar28;
  uint uVar29;
  uint uVar30;
  int iVar31;
  bool bVar32;
  undefined4 *local_ec;
  int local_d8;
  int local_d4;
  char *local_cc;
  byte local_c4;
  char local_c0;
  uint local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  char *local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined *local_88;
  ushort local_84;
  char local_68 [16];
  undefined4 local_58;
  char local_54 [8];
  undefined2 local_4c;
  
  bVar32 = "Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\x01';
  ppuVar27 = &PTR_caseD_4_0021a8a4;
  if (bVar32) {
    ppuVar27 = (undefined **)0x21987c;
  }
  ppuVar23 = &PTR_caseD_4_0021a850;
  if (bVar32) {
    ppuVar23 = (undefined **)0x219828;
  }
  uVar15 = 0x216f70;
  if (!bVar32) {
    uVar15 = 0x217388;
  }
  ppuVar21 = &PTR_caseD_4_0021a840;
  if (bVar32) {
    ppuVar21 = (undefined **)0x219818;
  }
  uVar22 = 0x2173b4;
  if (bVar32) {
    uVar22 = 0x216f90;
  }
  ppuVar14 = (undefined **)0x219848;
  if (!bVar32) {
    ppuVar14 = &PTR_caseD_4_0021a870;
  }
  uVar28 = 0x216f9c;
  ppuVar1 = (undefined **)0x219820;
  if (!bVar32) {
    uVar28 = 0x2173c0;
    ppuVar1 = &PTR_caseD_4_0021a848;
  }
  uVar24 = 0x216ef8;
  uVar2 = 0x2170ac;
  if (!bVar32) {
    uVar24 = 0x217320;
    uVar2 = 0x2174d8;
  }
  uVar17 = 0x216f94;
  if (!bVar32) {
    uVar17 = 0x2173b8;
  }
  local_b8 = 0;
  local_a0 = 0;
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  local_90 = 0;
  local_8c = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar14,&local_b8);
  uVar30 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar27,&local_b8);
  uVar25 = local_b8;
  uVar29 = (uVar30 << 0x10) >> 0x18;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar17,&local_b8);
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar24,&local_b8);
  uVar3 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,&local_b8);
  uVar4 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar22,&local_b8);
  uVar5 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar28,&local_b8);
  uVar6 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar15,&local_b8);
  uVar7 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar1,&local_b8);
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar21,&local_b8);
  uVar8 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar23,&local_b8);
  uVar18 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219824,&local_b8);
  uVar9 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar1,&local_b8);
  uVar19 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x21981c,&local_b8);
  uVar10 = local_b8;
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219838,&local_b8);
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\x01') {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2195a0,&local_a0);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x21959c,&local_94);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219680,&local_9c);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x21967c,&local_90);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219760,&local_98);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x21975c,&local_8c);
  }
  else {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2191c8,&local_a0);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2191c4,&local_94);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219ca8,&local_9c);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219ca4,&local_90);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&PTR_caseD_4_0021a788,&local_98);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&PTR_caseD_4_0021a784,&local_8c);
  }
  local_c4 = (byte)uVar30;
  local_c0 = (char)(uVar25 >> 8);
  if ((((0 < DebugLevel) &&
       (printk("================FW DBG INFO===================\n"), 0 < DebugLevel)) &&
      (printk("       exp_assert_proc_entry_cnt = 0x%x\n",uVar29), 0 < DebugLevel)) &&
     (printk("       exp_assert_state = 0x%x\n",uVar30 & 0xff), 0 < DebugLevel)) {
    printk("       dic_exp_type = 0x%x\n",uVar25 >> 8 & 0xff);
  }
  if (uVar29 == 0) {
    pcVar12 = "exp_type : Normal";
    local_d8 = 0;
LAB_001947bc:
    local_68._0_4_ = *(undefined4 *)pcVar12;
    local_68._4_4_ = *(undefined4 *)(pcVar12 + 4);
    local_68._8_4_ = *(undefined4 *)(pcVar12 + 8);
    local_68._12_4_ = *(undefined4 *)(pcVar12 + 0xc);
    local_58._0_2_ = (short)*(undefined4 *)(pcVar12 + 0x10);
    local_d4 = local_d8;
  }
  else {
    if (local_c4 < 2 || uVar29 != 1) {
      local_d4 = 0;
      if (uVar29 != 1) {
        local_d8 = 1;
        builtin_strncpy(local_68,"exp_type : Excep",0x10);
        local_58._0_1_ = 't';
        local_58._1_1_ = 'i';
        local_58._2_1_ = 'o';
        local_58._3_1_ = 'n';
        builtin_strncpy(local_54," re-entr",8);
        local_4c = 0x79;
        goto LAB_001941d4;
      }
      local_68[8] = ' ';
      local_68[9] = ':';
      local_68[10] = ' ';
      local_68[0xb] = 'U';
      local_68[0xc] = 'n';
      local_68[0xd] = 'k';
      local_68[0xe] = 'n';
      local_68[0xf] = 'o';
      pcVar12 = "exp_type : Unknown\'?";
      local_d8 = 0;
    }
    else {
      if (local_c0 == '\x05') {
        pcVar12 = "exp_type : Assert";
        local_d8 = 1;
        goto LAB_001947bc;
      }
      local_d8 = 1;
      local_68[8] = ' ';
      local_68[9] = ':';
      local_68[10] = ' ';
      local_68[0xb] = 'E';
      local_68[0xc] = 'x';
      local_68[0xd] = 'c';
      local_68[0xe] = 'e';
      local_68[0xf] = 'p';
      pcVar12 = "exp_type : Exception";
    }
    local_d4 = 0;
    local_68[4] = 't';
    local_68[5] = 'y';
    local_68[6] = 'p';
    local_68[7] = 'e';
    local_68[0] = 'e';
    local_68[1] = 'x';
    local_68[2] = 'p';
    local_68[3] = '_';
    local_58 = *(undefined4 *)(pcVar12 + 0x10);
    local_54[0] = (char)*(undefined4 *)(pcVar12 + 0x10 + 4);
  }
LAB_001941d4:
  local_cc = local_68;
  if (DebugLevel < 1) {
LAB_001941dc:
    if (local_d8 != 0) {
LAB_001941ec:
      uVar30 = uVar18 >> 8 & 0xff;
      if (0x3b < uVar30) {
        uVar30 = 0x3c;
      }
      if (uVar30 != 0) {
LAB_00194210:
        uVar18 = uVar18 & 0xff;
        uVar25 = 0;
        do {
          uVar25 = uVar25 + 1;
          iVar16 = (short)uVar18 * 0xc + uVar9;
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16,&local_b4);
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16 + 4,&local_b0);
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16 + 8,&local_ac);
          if (0 < DebugLevel) {
            printk("       (sched_info_%d)sched_t=0x%x, sched_start=%d, PC=0x%x\n",uVar18,local_b4,
                   local_b0,local_ac);
          }
          uVar18 = uVar18 + 1 & 0xff;
          if (uVar30 <= uVar18) {
            uVar18 = 0;
          }
        } while (uVar25 < uVar30);
        goto LAB_0019428c;
      }
      goto LAB_00194298;
    }
  }
  else {
    printk("       COS_Interrupt_Count = 0x%x\n",0);
    if ((DebugLevel < 1) ||
       (printk("       processing_irqx = 0x%x\n",uVar3 >> 0x10), DebugLevel < 1)) goto LAB_00194b64;
    printk("       processing_lisr = 0x%x\n",uVar4);
    if ((DebugLevel < 1) || (printk("       Current_Task_Id = 0x%x\n",uVar5), DebugLevel < 1))
    goto LAB_001941dc;
    printk("       Current_Task_Indx = 0x%x\n",uVar6);
    if ((DebugLevel < 1) || (printk("       last_dequeued_msg_id = %d\n",uVar7), DebugLevel < 1))
    goto LAB_00194b64;
    printk("       km_irq_info_idx = 0x%x\n",uVar19 & 0xff);
    if ((DebugLevel < 1) ||
       (printk("       km_eint_info_idx = 0x%x\n",uVar8 & 0xff), DebugLevel < 1)) goto LAB_001941dc;
    printk("       km_sched_info_idx = 0x%x\n",uVar18 & 0xff);
    if (DebugLevel < 1) {
LAB_00194b64:
      if (local_d8 == 0) goto LAB_00194318;
      goto LAB_001941ec;
    }
    uVar30 = uVar18 >> 8 & 0xff;
    printk("       g_sched_history_num = %d\n",uVar30);
    if (DebugLevel < 1) goto LAB_00194b64;
    printk("       km_sched_trace_ptr = 0x%x\n",uVar9);
    if (local_d8 == 0) goto LAB_00194310;
    if (DebugLevel < 1) goto LAB_001941ec;
    printk("\n        <1>print sched trace\n");
    if (0x3b < uVar30) {
      uVar30 = 0x3c;
    }
    if (uVar30 != 0) goto LAB_00194210;
LAB_0019428c:
    if (0 < DebugLevel) {
      printk("\n        <2>print irq trace\n");
    }
LAB_00194298:
    uVar30 = (uVar19 << 0x10) >> 0x18;
    if (0x3b < uVar30) {
      uVar30 = 0x3c;
    }
    if (uVar30 != 0) {
      uVar19 = uVar19 & 0xff;
      uVar25 = 0;
      do {
        uVar25 = uVar25 + 1;
        iVar16 = (short)uVar19 * 0x10 + uVar10;
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16,&local_b4);
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16 + 4,&local_b0);
        if (0 < DebugLevel) {
          printk("       (irq_info_%d)irq_t=%x, sched_start=%d\n",uVar19,local_b4,local_b0);
        }
        uVar19 = uVar19 + 1 & 0xff;
        if (uVar30 <= uVar19) {
          uVar19 = 0;
        }
      } while (uVar25 != uVar30);
    }
  }
LAB_00194310:
  if ((((0 < DebugLevel) && (printk("\n       <3>task q_id.read q_id.write\n"), 0 < DebugLevel)) &&
      (printk("       (WMT )0 0x%x 0x%x\n",local_a0,local_94), 0 < DebugLevel)) &&
     (((printk("       (WIFI )1 0x%x 0x%x\n",local_9c,local_90), 0 < DebugLevel &&
       (printk("       (WIFI2 )2 0x%x 0x%x\n",local_98,local_8c), 0 < DebugLevel)) &&
      (printk("\n       <4>TASK STACK INFO (size in byte)\n"), 0 < DebugLevel)))) {
    printk("       TASK  START       END       SIZE  PEAK  INTEGRITY\n");
  }
LAB_00194318:
  local_ec = &local_ac;
  iVar16 = 0x219558;
  iVar31 = 1;
  iVar26 = 0;
  do {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16,&local_b4);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16 + -4,&local_b0);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16 + 8,local_ec);
    if (iVar26 == 0) {
      local_88 = &DAT_00544d57;
LAB_00194c00:
      if (0 < DebugLevel) {
LAB_00194c0c:
        printk("       %s  0x%x  0x%x  %d\n",&local_88,local_b4,local_b0,local_ac);
        goto LAB_001943a8;
      }
    }
    else {
      if (iVar26 == 1) {
        local_88 = (undefined *)0x49464957;
        local_84 = local_84 & 0xff00;
        goto LAB_00194c00;
      }
      local_88 = (undefined *)0x49464957;
      local_84 = 0x32;
      if (0 < DebugLevel) goto LAB_00194c0c;
LAB_001943a8:
      if (iVar31 == 3) break;
    }
    iVar26 = iVar26 + 1;
    iVar16 = iVar16 + 0xe0;
    iVar31 = iVar31 + 1;
  } while( true );
  if ((0 < DebugLevel) && (printk("\n       <5>fw state\n"), 0 < DebugLevel)) {
    printk("       %s\n",local_cc);
  }
  if (uVar6 == 3 && uVar5 == 0) {
    if (DebugLevel < 1) goto LAB_0019443c;
    printk("FW in IDLE\n");
  }
  if ((uVar5 != 0 && uVar6 != 3) && (0 < DebugLevel)) {
    printk("       FW in Task , Task id(0x%x) Task index(0x%x)\n",uVar5);
  }
LAB_0019443c:
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f080,&local_b8);
  if (0 < DebugLevel) {
    printk("       EXCP_CNT = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f084,&local_b8);
  if (0 < DebugLevel) {
    printk("       EXCP_TYPE = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f088,&local_b8);
  if (0 < DebugLevel) {
    printk("       CPU_ITYPE = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f08c,&local_b8);
  if (0 < DebugLevel) {
    printk("       CPU_EVA = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f090,&local_b8);
  if (0 < DebugLevel) {
    printk("       CPU_MERR = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f094,&local_b8);
  if (0 < DebugLevel) {
    printk("       CPU_IPC = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f098,&local_b8);
  if (0 < DebugLevel) {
    printk("       1ST_EXCP_TYPE = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f09c,&local_b8);
  if (0 < DebugLevel) {
    printk("       1ST_CPU_ITYPE = 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f0a0,&local_b8);
  if (0 < DebugLevel) {
    printk("       1ST_CPU_EVA= 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f0a4,&local_b8);
  if (0 < DebugLevel) {
    printk("       1ST_CPU_MERR= 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f0a8,&local_b8);
  if (0 < DebugLevel) {
    printk("       1ST_CPU_IPC= 0x%x\n",local_b8);
  }
  local_b8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c060204,&local_b8);
  if (0 < DebugLevel) {
    printk("       PC = 0x%x\n\n\n",local_b8);
  }
  ShowLpHistory(param_1,local_d8);
  ShowIrqHistory(param_1);
  ShowFwDbgCnt(param_1);
  ShowCpuUtilSum(param_1);
  ShowMsgTrace(param_1);
  ShowMsgWatch(param_1);
  ShowSchduleTrace(param_1);
  ShowProgTrace(param_1);
  if (local_d4 != 0) {
    local_a4 = 0;
    os_alloc_mem(0,&local_a8,0x100);
    if (local_a8 != (char *)0x0) {
      __memzero(local_a8,0x100);
      iVar16 = -0x1ffc4c00;
      pcVar12 = local_a8;
      do {
        local_a4 = 0;
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar16,&local_a4);
        pcVar20 = local_a8;
        iVar16 = iVar16 + 4;
        *(undefined4 *)pcVar12 = local_a4;
        pcVar12 = pcVar12 + 4;
      } while (iVar16 != -0x1ffc4b80);
      pcVar11 = strchr(local_a8,10);
      pcVar12 = strchr(pcVar11 + 1,10);
      if (pcVar12 < pcVar20 + 0x100) {
        do {
          pcVar13 = pcVar12 + 1;
          *pcVar12 = '\0';
          pcVar12 = pcVar13;
          pcVar20 = local_a8;
        } while (pcVar13 < local_a8 + 0x100);
      }
      if (((0 < DebugLevel) && (printk(&_LC535), pcVar20 = local_a8, 0 < DebugLevel)) &&
         (printk("       Assert line\n"), pcVar20 = local_a8, 0 < DebugLevel)) {
        printk("       %s\n",pcVar11 + 1);
        pcVar20 = local_a8;
      }
      os_free_mem(pcVar20);
    }
  }
  if (0 < DebugLevel) {
    printk("============================================\n");
  }
  return 0;
}

