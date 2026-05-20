// module: mt7915.ko
// function: hqa_mu_set_trigger_mu_tx @ 0x939e8
// size: 860 bytes
//

undefined4 hqa_mu_set_trigger_mu_tx(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  char *local_4c [2];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_4c[0] = param_2;
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_set_trigger_mu_tx");
      goto LAB_00093b78;
    }
LAB_00093bb8:
    uVar3 = 0;
  }
  else {
    pcVar2 = strsep(local_4c,":");
    if (pcVar2 == (char *)0x0) {
      if (DebugLevel < 0) goto LAB_00093bb8;
      printk("%s: RandomPattern is NULL\n","hqa_mu_set_trigger_mu_tx");
LAB_00093b78:
      if (DebugLevel < 0) goto LAB_00093bb8;
      uVar3 = 0;
      pcVar2 = "Fail";
    }
    else {
      uVar1 = os_str_tol(pcVar2,0,10);
      pcVar2 = strsep(local_4c,":");
      if (pcVar2 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00093bb8;
        printk("%s: MsduPayloadLength0 is NULL\n","hqa_mu_set_trigger_mu_tx");
        goto LAB_00093b78;
      }
      uVar3 = os_str_tol(pcVar2,0,10);
      pcVar2 = strsep(local_4c,":");
      if (pcVar2 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00093bb8;
        printk("%s: MsduPayloadLength1 is NULL\n","hqa_mu_set_trigger_mu_tx");
        goto LAB_00093b78;
      }
      uVar4 = os_str_tol(pcVar2,0,10);
      pcVar2 = strsep(local_4c,":");
      if (pcVar2 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00093bb8;
        printk("%s: MsduPayloadLength2 is NULL\n","hqa_mu_set_trigger_mu_tx");
        goto LAB_00093b78;
      }
      uVar5 = os_str_tol(pcVar2,0,10);
      pcVar2 = strsep(local_4c,":");
      if (pcVar2 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00093bb8;
        printk("%s: MsduPayloadLength3 is NULL\n","hqa_mu_set_trigger_mu_tx");
        goto LAB_00093b78;
      }
      uVar6 = os_str_tol(pcVar2,0,10);
      pcVar2 = strsep(local_4c,":");
      if (pcVar2 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00093bb8;
        printk("%s: MuPacketCount is NULL\n","hqa_mu_set_trigger_mu_tx");
        goto LAB_00093b78;
      }
      uVar7 = os_str_tol(pcVar2,0,10);
      if (local_4c[0] == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00093bb8;
        printk("%s: NumOfSTA is NULL\n","hqa_mu_set_trigger_mu_tx");
        goto LAB_00093b78;
      }
      local_2c = os_str_tol(local_4c[0],0,10);
      local_44 = CONCAT31(local_44._1_3_,uVar1);
      local_40 = uVar3;
      local_3c = uVar4;
      local_38 = uVar5;
      local_34 = uVar6;
      local_30 = uVar7;
      if (0 < DebugLevel) {
        printk("%s: RndPtrn:%u PayloadLen[0~3]:%u %u %u %u PktCnt:%u NumSta:%u\n",
               "hqa_mu_set_trigger_mu_tx",uVar1,uVar3,uVar4,uVar5,uVar6,uVar7,local_2c);
      }
      iVar8 = hqa_wifi_test_mu_trigger_mu_tx(param_1,&local_44);
      if (iVar8 != 0) goto LAB_00093b78;
      if (DebugLevel < 0) {
        return 1;
      }
      uVar3 = 1;
      pcVar2 = "Success";
    }
    printk("%s: CMD %s\n","hqa_mu_set_trigger_mu_tx",pcVar2);
  }
  return uVar3;
}

