// module: tm.ko
// function: tm_up_sch_sharp_total_cfg_print @ 0x54804
// size: 1900 bytes
//

undefined4 tm_up_sch_sharp_total_cfg_print(uint param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (0x1f < param_1) {
    printk("[tm][api]tm_up_sch_sharp_total_cfg_print input invalid tcont!!!\n");
    return 0xffffffff;
  }
  switch(param_2) {
  case 0:
    printk("**************** SCH GLOBAL ENABLE CFG INFO *************\n");
    printk("%-11s%-12s%-13s%-9s%-10s%-11s%-12s\n","TcontShpEn","QueschShpEn","SecschDwrrEn",
           "QueShpEn","QueDwrrEn","QueHwAgeEn","QueHwAgeMod");
    iVar2 = sch_get_tcont_sharp_enable(&local_48);
    iVar1 = sch_get_quesch_sharp_enable(&local_44);
    iVar7 = sch_get_secsch_dwrr_enable(&local_40);
    iVar5 = sch_get_que_sharp_enable(&local_3c);
    iVar6 = sch_get_dwrr_enable(&local_38);
    iVar4 = sch_get_hw_up_age_enable(&local_34);
    iVar3 = sch_get_hw_up_age_mode(&local_30);
    if ((((((iVar1 == 0 && iVar2 == 0) && iVar7 == 0) && iVar5 == 0) && iVar6 == 0) && iVar4 == 0)
        && iVar3 == 0) {
      printk("%-11d%-12d%-13d%-9d%-10d%-11d%-12d\n",local_48,local_44,local_40,local_3c,local_38,
             local_34,local_30);
      return 0;
    }
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_29363,"tm_up_sch_sharp_total_cfg_print"), iVar2 != 0)) {
      printk("ERROR:(%s:%d)tm_up_sch_sharp_total_cfg_print failed!\n","tm_api.c",0x478a);
      return 0xffffffff;
    }
    break;
  case 1:
    printk("**************** SCH QUEUE SCH SHP CFG INFO *************\n");
    printk("%-6s%-4s%-7s%-8s%-8s%-8s%-8s\n","Tcont",&_LC620,"SchMod","Weight","ShpRate","ShpFill",
           "ShpCap");
    iVar2 = 0;
    while( true ) {
      iVar1 = sch_get_up_que_sp_dwrr_cfg(param_1,iVar2,&local_60);
      iVar7 = sch_get_up_queue_wrr_weight(param_1,iVar2,&local_6c);
      iVar5 = tm_tcont_que_sharp_get(param_1,iVar2,&local_5c);
      iVar6 = sch_get_up_pq_sharp_fill_rate(param_1,iVar2,&local_68);
      iVar4 = sch_get_up_pq_sharp_bucket_cap(param_1,iVar2,&local_64);
      if ((((iVar7 != 0 || iVar1 != 0) || iVar5 != 0) || iVar6 != 0) || iVar4 != 0) break;
      iVar1 = iVar2 + 1;
      printk("%-6d%-4d%-7d%-8d%-8d%-8d%-8d\n",param_1,iVar2,local_60,local_6c,local_5c,local_68,
             local_64);
      iVar2 = iVar1;
      if (iVar1 == 8) {
        return 0;
      }
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_29368,"tm_up_sch_sharp_total_cfg_print");
    if (iVar2 == 0) {
      return 0xffffffff;
    }
    printk("ERROR:(%s:%d)tm_up_sch_sharp_total_cfg_print failed!\n","tm_api.c",0x479b);
    return 0xffffffff;
  case 2:
    printk("**************** SCH SECOND SCH SHP CFG INFO *************\n");
    printk("%-6s%-6s%-7s%-8s%-8s%-8s%-8s\n","Tcont","SchId","SchMod","Weight","ShpRate","ShpFill",
           "ShpCap");
    local_70 = 0;
    while( true ) {
      iVar2 = sch_get_secsch_sp_dwrr_cfg(param_1,local_70,&local_60);
      iVar1 = sch_get_secsch_wrr_weight(param_1,local_70,&local_6c);
      iVar7 = tm_tcont_secsch_sharp_get(param_1,local_70,&local_5c);
      iVar5 = sch_get_quesch_sharp_fill_rate(param_1,local_70,&local_68);
      iVar6 = sch_get_quesch_sharp_bucket_cap(param_1,local_70,&local_64);
      if ((((iVar1 != 0 || iVar2 != 0) || iVar7 != 0) || iVar5 != 0) || iVar6 != 0) break;
      printk("%-6d%-6d%-7d%-8d%-8d%-8d%-8d\n",param_1,local_70,local_60,local_6c,local_5c,local_68,
             local_64);
      local_70 = local_70 + 1;
      if (3 < local_70) {
        return 0;
      }
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_29374,"tm_up_sch_sharp_total_cfg_print");
    if (iVar2 == 0) {
      return 0xffffffff;
    }
    printk("ERROR:(%s:%d)tm_up_sch_sharp_total_cfg_print failed!\n","tm_api.c",0x47ad);
    return 0xffffffff;
  case 3:
    printk("**************** SCH TCONT SHP CFG INFO *************\n");
    printk("%-6s%-8s%-8s%-8s\n","Tcont","ShpRate","ShpFill","ShpCap");
    iVar2 = tm_tcont_sharp_get(param_1,&local_5c);
    iVar1 = sch_get_up_tcont_sharp_fill_rate(param_1,&local_68);
    iVar7 = sch_get_up_tcont_sharp_bucket_cap(param_1,&local_64);
    if ((iVar1 == 0 && iVar2 == 0) && iVar7 == 0) {
      printk("%-6d%-8d%-8d%-8d\n",param_1,local_5c,local_68,local_64);
      return 0;
    }
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_29380,"tm_up_sch_sharp_total_cfg_print"), iVar2 != 0)) {
      printk("ERROR:(%s:%d)tm_up_sch_sharp_total_cfg_print failed!\n","tm_api.c",0x47bb);
      return 0xffffffff;
    }
    break;
  case 4:
    printk("**************** SCH SECOND SCH HANG QUE INFO *************\n");
    printk("%-6s%-4s%-9s\n","Tcont",&_LC620,"SecSchId");
    iVar2 = 0;
    while (iVar1 = tm_tcont_secsch_hang_que_get(param_1,iVar2,&local_70), iVar1 == 0) {
      iVar1 = iVar2 + 1;
      printk("%-6d%-4d%-9d\n",param_1,iVar2,local_70);
      iVar2 = iVar1;
      if (iVar1 == 8) {
        printk("**************** SCH SECOND SCH HANG QUE MASK *************\n");
        printk("%-6s %s\n","Tcont","ena_msk");
        sch_get_quesch_mount_tcont_que(param_1,&local_58);
        printk("%-6d 0x%x:%x:%x:%x\n",param_1,local_4c,local_50,local_54,local_58);
        return 0;
      }
    }
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_29383,"tm_up_sch_sharp_total_cfg_print"), iVar2 != 0)) {
      printk("ERROR:(%s:%d)tm_tcont_secsch_hang_que_get failed!\n","tm_api.c",0x47c8);
      return 0xffffffff;
    }
    break;
  case 5:
    printk("**************** SCH QUEUE LAST PKTS IN BUF *************\n");
    printk("%-6s%-4s%-10s\n","Tcont",&_LC620,"LastPkts");
    iVar2 = 0;
    while (iVar1 = sch_get_up_queue_last_pkt_cnt(param_1,iVar2,&local_5c), iVar1 == 0) {
      iVar1 = iVar2 + 1;
      printk("%-6d%-4d%-10d\n",param_1,iVar2,local_5c);
      iVar2 = iVar1;
      if (iVar1 == 8) {
        return 0;
      }
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_29389,"tm_up_sch_sharp_total_cfg_print");
    if (iVar2 == 0) {
      return 0xffffffff;
    }
    printk("ERROR:(%s:%d)tm_up_sch_sharp_total_cfg_print failed!\n","tm_api.c",0x47db);
    return 0xffffffff;
  default:
    printk("invalid parameter!!!\n");
  }
  return 0xffffffff;
}

