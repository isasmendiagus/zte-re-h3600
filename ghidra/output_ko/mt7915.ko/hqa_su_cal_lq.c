// module: mt7915.ko
// function: hqa_su_cal_lq @ 0x920e4
// size: 808 bytes
//

undefined4 hqa_su_cal_lq(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined2 uVar6;
  char *pcVar7;
  int iVar8;
  undefined4 uVar9;
  char *local_3c [2];
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_32 = 0;
  local_30 = 0;
  local_2e = 0;
  local_2c = 0;
  local_2a = 0;
  local_3c[0] = param_2;
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_su_cal_lq");
      goto LAB_00092248;
    }
LAB_00092284:
    uVar9 = 0;
  }
  else {
    pcVar7 = strsep(local_3c,":");
    if (pcVar7 == (char *)0x0) {
      if (DebugLevel < 0) goto LAB_00092284;
      printk("%s: NumOfUser is NULL\n","hqa_su_cal_lq");
LAB_00092248:
      if (DebugLevel < 1) goto LAB_00092284;
      uVar9 = 0;
      pcVar7 = "Fail";
    }
    else {
      uVar1 = os_str_toul(pcVar7,0,10);
      pcVar7 = strsep(local_3c,":");
      if (pcVar7 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092284;
        printk("%s: Bandwidth is NULL\n","hqa_su_cal_lq");
        goto LAB_00092248;
      }
      uVar2 = os_str_toul(pcVar7,0,10);
      pcVar7 = strsep(local_3c,":");
      if (pcVar7 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092284;
        printk("%s: NssOfUser0 is NULL\n","hqa_su_cal_lq");
        goto LAB_00092248;
      }
      uVar3 = os_str_toul(pcVar7,0,10);
      pcVar7 = strsep(local_3c,":");
      if (pcVar7 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092284;
        printk("%s: PFMUIDOfUser0 is NULL\n","hqa_su_cal_lq");
        goto LAB_00092248;
      }
      uVar4 = os_str_toul(pcVar7,0,10);
      pcVar7 = strsep(local_3c,":");
      if (pcVar7 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092284;
        printk("%s: NumOfTxer is NULL\n","hqa_su_cal_lq");
        goto LAB_00092248;
      }
      uVar5 = os_str_toul(pcVar7,0,10);
      if (local_3c[0] == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092284;
        printk("%s: GroupIndex is NULL\n","hqa_su_cal_lq");
        goto LAB_00092248;
      }
      uVar6 = os_str_toul(local_3c[0],0,10);
      os_zero_mem(&local_32,10);
      local_32 = CONCAT11(uVar2,uVar1);
      local_30 = CONCAT11(uVar4,uVar3);
      local_2e = CONCAT11(local_2e._1_1_,uVar5);
      local_2a = uVar6;
      if (0 < DebugLevel) {
        printk("%s: NumUser:%u, BW:%u, Nss0:%u PFMUID:%u NTxer:%u GroupIndex:%u\n","hqa_su_cal_lq",
               uVar1,uVar2,uVar3,uVar4,uVar5,uVar6);
      }
      iVar8 = hqa_wifi_test_su_cal_lq(param_1,&local_32);
      if (iVar8 != 0) goto LAB_00092248;
      if (DebugLevel < 1) {
        return 1;
      }
      uVar9 = 1;
      pcVar7 = "Success";
    }
    printk("%s: CMD %s\n","hqa_su_cal_lq",pcVar7);
  }
  return uVar9;
}

