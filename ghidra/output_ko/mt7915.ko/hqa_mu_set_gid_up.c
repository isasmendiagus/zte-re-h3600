// module: mt7915.ko
// function: hqa_mu_set_gid_up @ 0x936f0
// size: 756 bytes
//

undefined4 hqa_mu_set_gid_up(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  char *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_3c = param_2;
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_set_gid_up");
      goto LAB_00093830;
    }
LAB_0009386c:
    uVar2 = 0;
  }
  else {
    pcVar1 = strsep(&local_3c,":");
    if (pcVar1 == (char *)0x0) {
      if (DebugLevel < 0) goto LAB_0009386c;
      printk("%s: GroupID0 is NULL\n","hqa_mu_set_gid_up");
LAB_00093830:
      if (DebugLevel < 1) goto LAB_0009386c;
      uVar2 = 0;
      pcVar1 = "Fail";
    }
    else {
      uVar2 = os_str_tol(pcVar1,0,10);
      pcVar1 = strsep(&local_3c,":");
      if (pcVar1 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_0009386c;
        printk("%s: GroupID1 is NULL\n","hqa_mu_set_gid_up");
        goto LAB_00093830;
      }
      uVar3 = os_str_tol(pcVar1,0,10);
      pcVar1 = strsep(&local_3c,":");
      if (pcVar1 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_0009386c;
        printk("%s: UserPosition0 is NULL\n","hqa_mu_set_gid_up");
        goto LAB_00093830;
      }
      uVar4 = os_str_tol(pcVar1,0,10);
      pcVar1 = strsep(&local_3c,":");
      if (pcVar1 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_0009386c;
        printk("%s: UserPosition1 is NULL\n","hqa_mu_set_gid_up");
        goto LAB_00093830;
      }
      uVar5 = os_str_tol(pcVar1,0,10);
      pcVar1 = strsep(&local_3c,":");
      if (pcVar1 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_0009386c;
        printk("%s: UserPosition2 is NULL\n","hqa_mu_set_gid_up");
        goto LAB_00093830;
      }
      uVar6 = os_str_tol(pcVar1,0,10);
      if (local_3c == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_0009386c;
        printk("%s: UserPosition3 is NULL\n","hqa_mu_set_gid_up");
        goto LAB_00093830;
      }
      local_24 = os_str_tol(local_3c,0,10);
      local_38 = uVar2;
      local_34 = uVar3;
      local_30 = uVar4;
      local_2c = uVar5;
      local_28 = uVar6;
      if (0 < DebugLevel) {
        printk("%s: GID[0~1]=0x%x 0x%x UP[0~3]=0x%x 0x%x 0x%x 0x%x\n","hqa_mu_set_gid_up",uVar2,
               uVar3,uVar4,uVar5,uVar6,local_24);
      }
      iVar7 = hqa_wifi_test_mu_set_sta_gid_and_up(param_1,&local_38);
      if (iVar7 != 0) goto LAB_00093830;
      if (DebugLevel < 1) {
        return 1;
      }
      uVar2 = 1;
      pcVar1 = "Success";
    }
    printk("%s: CMD %s\n","hqa_mu_set_gid_up",pcVar1);
  }
  return uVar2;
}

