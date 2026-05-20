// module: mt7915.ko
// function: hqa_mu_cal_lq @ 0x91a70
// size: 1480 bytes
//

undefined4 hqa_mu_cal_lq(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined2 uVar12;
  char *pcVar13;
  int iVar14;
  undefined4 uVar15;
  char *local_3c;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined1 local_30;
  undefined1 uStack_2f;
  undefined1 local_2e;
  undefined1 uStack_2d;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_36 = 0;
  local_34 = 0;
  local_32 = 0;
  local_30 = 0;
  uStack_2f = 0;
  local_2e = 0;
  uStack_2d = 0;
  local_2c = 0;
  local_2a = 0;
  local_3c = param_2;
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_cal_lq");
      goto LAB_00091d18;
    }
LAB_00091d54:
    uVar15 = 0;
  }
  else {
    pcVar13 = strsep(&local_3c,":");
    if (pcVar13 == (char *)0x0) {
      if (DebugLevel < 0) goto LAB_00091d54;
      printk("%s: NumOfUser is NULL\n","hqa_mu_cal_lq");
LAB_00091d18:
      if (DebugLevel < 1) goto LAB_00091d54;
      uVar15 = 0;
      pcVar13 = "Fail";
    }
    else {
      uVar1 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: Bandwidth is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar2 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: NssOfUser0 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar3 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: NssOfUser1 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar4 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: NssOfUser2 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar5 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: NssOfUser3 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar6 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: PfmuIdOfUser0 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar7 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: PfmuIdOfUser1 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar8 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: PfmuIdOfUser2 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar9 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: PfmuIdOfUser3 is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar10 = os_str_toul(pcVar13,0,10);
      pcVar13 = strsep(&local_3c,":");
      if (pcVar13 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: NumOfTxer is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar11 = os_str_toul(pcVar13,0,10);
      if (local_3c == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00091d54;
        printk("%s: GroupIndex is NULL\n","hqa_mu_cal_lq");
        goto LAB_00091d18;
      }
      uVar12 = os_str_toul(local_3c,0,10);
      os_zero_mem(&local_36,0xe);
      local_36 = CONCAT11(uVar2,uVar1);
      local_34 = CONCAT11(uVar4,uVar3);
      local_32 = CONCAT11(uVar6,uVar5);
      local_2c = CONCAT11(local_2c._1_1_,uVar11);
      local_2a = uVar12;
      local_2e = uVar9;
      uStack_2d = uVar10;
      local_30 = uVar7;
      uStack_2f = uVar8;
      if ((0 < DebugLevel) &&
         (printk("%s: Num_User:%u, BW:%u, Nss[0~3]:%u %u %u %u\n","hqa_mu_cal_lq",uVar1,uVar2,uVar3,
                 uVar4,uVar5,uVar6), 0 < DebugLevel)) {
        printk("%s: PFID[0~3]:%u %u %u %u Num_Txer:%u GroupIndex:%u\n","hqa_mu_cal_lq",local_30,
               uStack_2f,local_2e,uStack_2d,(undefined1)local_2c,local_2a);
      }
      iVar14 = hqa_wifi_test_mu_cal_lq(param_1,&local_36);
      if (iVar14 != 0) goto LAB_00091d18;
      if (DebugLevel < 1) {
        return 1;
      }
      uVar15 = 1;
      pcVar13 = "Success";
    }
    printk("%s: CMD %s\n","hqa_mu_cal_lq",pcVar13);
  }
  return uVar15;
}

