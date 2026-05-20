// module: mt7915.ko
// function: muruEventDispatcher @ 0x238cec
// size: 2600 bytes
//

void muruEventDispatcher(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 uVar4;
  short *psVar5;
  int iVar6;
  undefined4 *puVar7;
  
  uVar4 = *param_2;
  if (0 < DebugLevel) {
    printk("%s: u4EventId = %u, len = %u\n","muruEventDispatcher",uVar4,param_3);
  }
  switch(uVar4) {
  case 0xe:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        return;
      }
    }
    else {
      printk("%s: MURU_EVENT_GET_BSRP_CTRL\n","muruEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_bsrp_ctrl_handler";
        pcVar2 = "%s: rsp_payload is null!!\n";
        goto LAB_002393f4;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_bsrp_ctrl_handler";
LAB_0023942c:
        pcVar2 = "%s: msg is null!!\n";
        goto LAB_002393f4;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_bsrp_ctrl_handler";
        pcVar2 = "%s: Error !! buffer not specified by cmd\n";
        goto LAB_002393f4;
      }
    }
    if (((0 < DebugLevel) &&
        (printk("%s:MURU_EVENT_GET_BSRP_CTRL\n","muru_get_bsrp_ctrl_handler"), 0 < DebugLevel)) &&
       (printk("eventId %u\n",*param_2), 0 < DebugLevel)) {
      printk("u1TriggerFlow:%u, u2BsrpInterval:%u, u2BsrpRuAlloc:%u, u4PpduDur:%u, fgExtCmdBsrp:%d\n"
             ,*(undefined1 *)(param_2 + 4),*(undefined2 *)(param_2 + 2),
             *(undefined2 *)((int)param_2 + 10),param_2[3],*(undefined1 *)((int)param_2 + 0x11));
    }
    break;
  case 0xf:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        return;
      }
    }
    else {
      printk("%s: MURU_EVENT_GET_GLOBAL_PROT_SEC_CTRL\n","muruEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_global_prot_sec_ctrl_handler";
        pcVar2 = "%s: rsp_payload is null!!\n";
        goto LAB_002393f4;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_global_prot_sec_ctrl_handler";
        goto LAB_0023942c;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_global_prot_sec_ctrl_handler";
        pcVar2 = "%s: Error !! buffer not specified by cmd\n";
        goto LAB_002393f4;
      }
    }
    if (DebugLevel < 1) {
      return;
    }
    printk("%s:EVENT_HQA_GET_SU_CALC_LQ\n","muru_get_global_prot_sec_ctrl_handler");
    if (DebugLevel < 1) {
LAB_00238f1c:
      if (0 < DebugLevel) {
        printk("ucProt = 0x%x\n",((uint)*(byte *)(param_2 + 1) << 0x19) >> 0x1e);
        if (DebugLevel < 1) {
          return;
        }
        printk("ucProtRuAlloc = 0x%x\n",*(byte *)((int)param_2 + 5) & 7);
        goto LAB_00238f64;
      }
    }
    else {
      printk("eventId %u\n",*param_2);
      if (DebugLevel < 1) {
        return;
      }
      printk("ucExp = 0x%x\n",*(byte *)(param_2 + 1) & 1);
      if (0 < DebugLevel) {
        printk("ucTxOp = 0x%x\n",((uint)*(byte *)(param_2 + 1) << 0x1e) >> 0x1f);
        if (DebugLevel < 1) {
          return;
        }
        printk("ucPdc = 0x%x\n",((uint)*(byte *)(param_2 + 1) << 0x1b) >> 0x1d);
        goto LAB_00238f1c;
      }
LAB_00238f64:
      if (DebugLevel < 1) {
        return;
      }
      printk("ucFixedRate = 0x%x\n",((uint)*(byte *)((int)param_2 + 5) << 0x1c) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("ucSuTx = 0x%x\n",((uint)*(byte *)((int)param_2 + 5) << 0x1b) >> 0x1f);
    }
    if ((0 < DebugLevel) &&
       (printk("ucTpPolicy = 0x%x\n",*(byte *)((int)param_2 + 5) >> 5), 0 < DebugLevel)) {
      pcVar2 = "ucTriggerFlow = 0x%x\n";
      pcVar3 = (char *)(*(byte *)((int)param_2 + 6) & 1);
LAB_002393f4:
      printk(pcVar2,pcVar3);
      return;
    }
    break;
  case 0x10:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        return;
      }
    }
    else {
      printk("%s: MURU_EVENT_GET_TX_DATA_SEC_CTRL\n","muruEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_tx_data_sec_ctrl_handler";
        pcVar2 = "%s: rsp_payload is null!!\n";
        goto LAB_002393f4;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_tx_data_sec_ctrl_handler";
        goto LAB_0023942c;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_tx_data_sec_ctrl_handler";
        pcVar2 = "%s: Error !! buffer not specified by cmd\n";
        goto LAB_002393f4;
      }
    }
    if (DebugLevel < 1) {
      return;
    }
    printk("%s:EVENT_HQA_GET_SU_CALC_LQ\n","muru_get_tx_data_sec_ctrl_handler");
    if (DebugLevel < 1) {
      return;
    }
    printk("eventId %u\n",*param_2);
    if (DebugLevel < 1) {
      return;
    }
    printk("ucBw = 0x%x\n",*(byte *)(param_2 + 1) & 7);
    if (DebugLevel < 1) {
      return;
    }
    pcVar2 = "ucMuPpduDur = 0x%x\n";
    pcVar3 = (char *)((uint)(param_2[1] << 0xf) >> 0x12);
    goto LAB_002393f4;
  case 0x11:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        return;
      }
    }
    else {
      printk("%s: MURU_EVENT_GET_TRIG_DATA_SEC_CTRL\n","muruEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_trig_data_sec_ctrl_handler";
        pcVar2 = "%s: rsp_payload is null!!\n";
        goto LAB_002393f4;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_trig_data_sec_ctrl_handler";
        goto LAB_0023942c;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_trig_data_sec_ctrl_handler";
        pcVar2 = "%s: Error !! buffer not specified by cmd\n";
        goto LAB_002393f4;
      }
    }
    if (DebugLevel < 1) {
      return;
    }
    printk("%s:EVENT_HQA_GET_SU_CALC_LQ\n","muru_get_trig_data_sec_ctrl_handler");
    if (DebugLevel < 1) {
      return;
    }
    printk("eventId %u\n",*param_2);
    if (DebugLevel < 1) {
      return;
    }
    printk("ucBaPolicy = 0x%x\n",*(byte *)(param_2 + 1) & 3);
    if (DebugLevel < 1) {
      return;
    }
    printk("ucGBABw = 0x%x\n",((uint)*(byte *)(param_2 + 1) << 0x1b) >> 0x1d);
    if (DebugLevel < 1) {
      return;
    }
    pcVar2 = "ucGBAMuPpduDur = 0x%x\n";
    pcVar3 = (char *)((uint)(param_2[1] << 0xd) >> 0x12);
    goto LAB_002393f4;
  case 0x13:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        return;
      }
    }
    else {
      printk("%s: MURU_EVENT_GET_HESND_CTRL\n","muruEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_hesnd_ctrl_handler";
        pcVar2 = "%s: rsp_payload is null!!\n";
        goto LAB_002393f4;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_hesnd_ctrl_handler";
        goto LAB_0023942c;
      }
      if (*(int *)(param_1 + 0xc) == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "muru_get_hesnd_ctrl_handler";
        pcVar2 = "%s: Error !! buffer not specified by cmd\n";
        goto LAB_002393f4;
      }
    }
    if (((0 < DebugLevel) &&
        (printk("%s:MURU_EVENT_GET_HESND_CTRL\n","muru_get_hesnd_ctrl_handler"), 0 < DebugLevel)) &&
       (printk("eventId %u\n",*param_2), 0 < DebugLevel)) {
      printk("ucTriggerFlow = %u, ucInterval:%u, ucBrRuAlloc:%u, ppduDur:%u\n",
             *(undefined1 *)((int)param_2 + 0xd),*(undefined1 *)(param_2 + 3),
             *(undefined2 *)((int)param_2 + 0xe),param_2[2]);
    }
    break;
  case 0x14:
    if (DebugLevel < 0) {
      if ((param_2 == (undefined4 *)0x0) || (param_1 == 0)) goto LAB_00239240;
LAB_0023922c:
      if (*(int *)(param_1 + 0xc) == 0) {
        if (DebugLevel < 0) goto LAB_00239240;
        printk("%s: Error !! buffer not specified by cmd\n","muru_get_mum_handler");
        goto switchD_00238d1c_caseD_15;
      }
    }
    else {
      printk("%s: MURU_EVENT_GET_MUM_CTRL\n","muruEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) goto LAB_00239240;
        printk("%s: rsp_payload is null!!\n","muru_get_mum_handler");
      }
      else {
        if (param_1 != 0) goto LAB_0023922c;
        if (DebugLevel < 0) goto LAB_00239240;
        printk("%s: msg is null!!\n","muru_get_mum_handler");
      }
    }
    goto LAB_00239238;
  case 0x15:
switchD_00238d1c_caseD_15:
LAB_00239238:
    if ((((-1 < DebugLevel) &&
         (printk("%s: MURU_EVENT_GET_ULTX_CNT\n","muruEventDispatcher"), 0 < DebugLevel)) &&
        (printk("%s:MURU_EVENT_GET_ULTX_CNT\n","muru_get_ul_tx_cnt_handler"), 0 < DebugLevel)) &&
       (printk("eventId %u\n",*param_2), 0 < DebugLevel)) {
      printk("StaCnt = %u\n",*(undefined1 *)(param_2 + 1));
    }
LAB_00239240:
    puVar7 = param_2 + 2;
    iVar1 = 0;
    do {
      if (0 < DebugLevel) {
        printk("WCID: %u, Packet Sent: %u, ok: %u\n",iVar1,*puVar7,puVar7[0x11]);
      }
      iVar1 = iVar1 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar1 <= (int)(uint)*(byte *)(param_2 + 1));
    return;
  case 0x16:
    if (-1 < DebugLevel) {
      printk("%s: MURU_EVENT_GET_SPL_CNT\n","muruEventDispatcher");
    }
    iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xa797a0));
    if ((0 < DebugLevel) &&
       (printk("%s:MURU_EVENT_GET_SPL_CNT\n","muru_get_spl_cnt_handler"), 0 < DebugLevel)) {
      printk("eventId %u\n",*param_2);
    }
    if (iVar1 != 0) {
      psVar5 = (short *)((int)param_2 + 2);
      iVar6 = 0;
      do {
        psVar5 = psVar5 + 1;
        if ((*psVar5 != 0) && (0 < DebugLevel)) {
          printk("WCID: %u, SPL Count: %u\n",iVar6);
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 != iVar1);
    }
    break;
  case 0x17:
    if (-1 < DebugLevel) {
      printk("%s: MURU_EVENT_GET_GLO_ADDR\n","muruEventDispatcher");
    }
    iVar6 = *(int *)(param_1 + 0x1c);
    iVar1 = hc_get_chip_ops(*(undefined4 *)(iVar6 + 0xa797a0));
    if ((0 < DebugLevel) &&
       (printk("%s:MURU_EVENT_GET_GLO_ADDR\n","muru_get_glo_addr_handler"), 0 < DebugLevel)) {
      printk("eventId %u\n",*param_2);
    }
    if (*(code **)(iVar1 + 0x29c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00238e4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(iVar1 + 0x29c))(iVar6,param_2 + 2);
      return;
    }
  }
  return;
}

