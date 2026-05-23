// module: mt7915.ko
// function: hqa_iBFSetValue_ext @ 0x278bc4
// size: 1824 bytes
//

undefined4 hqa_iBFSetValue_ext(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  char *__format;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  char *local_44;
  uint local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  
  local_50 = param_3 + 0xc;
  iVar2 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar2 + 0x4cc);
  net_ad_wrap_service(param_1);
  local_4c = 0;
  local_48 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  os_alloc_mem(param_1,&local_44,0x200);
  if (local_44 == (char *)0x0) {
    uVar3 = 3;
    goto LAB_00278da0;
  }
  FUN_00276034(1,4,&local_50,&local_4c);
  FUN_00276034(1,4,&local_50,&local_48);
  FUN_00276034(1,4,&local_50,&local_40);
  FUN_00276034(1,4,&local_50,&local_3c);
  FUN_00276034(1,4,&local_50,&local_38);
  FUN_00276034(1,4,&local_50,&local_34);
  FUN_00276034(1,4,&local_50,&local_30);
  FUN_00276034(1,4,&local_50,&local_2c);
  FUN_00276034(1,4,&local_50,&local_28);
  FUN_00276034(1,4,&local_50,local_24);
  switch(local_48) {
  case 1:
    __memzero(local_44,0x200);
    sprintf(local_44,"%d",local_40 & 0xff);
    SetATETxBfDutInitProc(param_1,local_44);
    break;
  case 2:
    __memzero(local_44,0x200);
    if (local_3c == 1) {
      __format = "%d:1";
    }
    else {
      __format = "%d";
    }
    sprintf(local_44,__format,local_40 & 0xff);
    SetATEChannel(param_1,local_44);
    break;
  case 3:
    __memzero(local_44,0x200);
    sprintf(local_44,"%d",local_40 & 0xff);
    SetATETxMcs(param_1,local_44);
    break;
  case 4:
    __memzero(local_44,0x200);
    sprintf(local_44,"%d",local_40 & 0xff);
    SetATETxPower0(param_1,local_44);
    break;
  case 5:
    __memzero(local_44,0x200);
    sprintf(local_44,"%d",local_40 & 0xff);
    SetATETxAntenna(param_1,local_44);
    break;
  case 6:
    SetATE(param_1,"TXSTOP");
    __memzero(local_44,0x200);
    builtin_strncpy(local_44,"RXFRAME",8);
    SetATE(param_1,local_44,local_44," ATE_IBF_PHASE_COMP is failed!!\n");
    break;
  case 7:
    __memzero(local_44,0x200);
    sprintf(local_44,"%d",local_40 & 0xff);
    SetATERxAntenna(param_1,local_44);
    break;
  case 8:
    __memzero(local_44,0x200);
    sprintf(local_44,"%d",local_40 & 0xff);
    SetATETxBfLnaGain(param_1,local_44);
    break;
  case 9:
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x:%02x:%02x",local_40,local_3c,local_38,local_34,local_30);
    iVar2 = SetATEIBfPhaseComp(param_1,local_44);
    if (iVar2 != 0) break;
    if (DebugLevel < 0) goto LAB_00278e58;
    uVar3 = 1;
    printk(" ATE_IBF_PHASE_COMP is failed!!\n");
    goto LAB_00278d90;
  case 10:
    local_38 = 0;
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
    iVar2 = SetATETxPacketWithBf(param_1,local_44);
    if (iVar2 != 0) break;
    if (DebugLevel < 0) goto LAB_00278e58;
    uVar3 = 1;
    printk(" ATE_IBF_TX is failed!!\n");
    goto LAB_00278d90;
  case 0xb:
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
    iVar2 = SetATEIBfProfileUpdate(param_1,local_44);
    if (iVar2 == 0) {
      if (DebugLevel < 0) {
LAB_00278e58:
        uVar3 = 1;
      }
      else {
        uVar3 = 1;
        printk(" ATE_IBF_PROF_UPDATE is failed!!\n");
      }
    }
    else {
      __memzero(local_44,0x200);
      builtin_strncpy(local_44,"01:00:01:00:01",0xf);
      iVar2 = Set_TxBfTxApply(param_1,local_44);
      if (iVar2 != 0) break;
      if (DebugLevel < 0) goto LAB_00278e58;
      uVar3 = 1;
      printk(" IBF flag setting in WTBL is failed!!\n");
    }
    goto LAB_00278d90;
  case 0xc:
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
    iVar2 = SetATEEBfProfileConfig(param_1,local_44);
    if (iVar2 != 0) break;
    if (DebugLevel < 0) goto LAB_00278e58;
    uVar3 = 1;
    printk(" ATE_EBF_PROF_UPDATE is failed!!\n");
    goto LAB_00278d90;
  case 0xd:
    iVar2 = net_ad_wrap_service(param_1);
    iVar4 = (uint)bVar1 * 0xd18;
    uVar5 = *(uint *)(iVar2 + iVar4 + 0x4e0);
    iVar2 = net_ad_wrap_service(param_1);
    *(uint *)(iVar2 + iVar4 + 0x4e0) = uVar5 | 0x400;
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x:%02x:%02x",local_40,local_3c,local_38,local_34,local_30);
    iVar2 = SetATEIBfInstCal(param_1,local_44);
    if (iVar2 != 0) break;
    if (DebugLevel < 0) goto LAB_00278e58;
    uVar3 = 1;
    printk(" ATE_IBF_GD_CAL is failed!!\n");
    goto LAB_00278d90;
  case 0xe:
    uVar3 = 1;
    iVar2 = net_ad_wrap_service(param_1);
    iVar4 = (uint)bVar1 * 0xd18;
    uVar5 = *(uint *)(iVar2 + iVar4 + 0x4e0);
    iVar2 = net_ad_wrap_service(param_1);
    local_34 = 4;
    *(uint *)(iVar2 + iVar4 + 0x4e0) = uVar5 | 0x400;
    local_30 = 1;
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x:%02x:%02x",local_40,local_3c,local_38,local_34,local_30);
    iVar2 = SetATEIBfInstCal(param_1,local_44);
    if (iVar2 != 0) break;
    if (DebugLevel < 0) goto LAB_00278e58;
    printk(" ATE_IBF_INST_VERIFY is failed!!\n");
    goto LAB_00278d90;
  case 0x10:
    __memzero(local_44,0x200);
    sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
    *(undefined1 *)(param_1 + 0xa7868c) = 0;
    iVar2 = SetATETxBfPhaseE2pUpdate(param_1,local_44);
    if (iVar2 != 0) break;
    if (DebugLevel < 0) goto LAB_00278e58;
    uVar3 = 1;
    printk(" ATE_IBF_PHASE_E2P_UPDATE is failed!!\n");
    goto LAB_00278d90;
  }
  uVar3 = 0;
  *(undefined4 *)(param_3 + 0xe) = local_4c;
LAB_00278d90:
  if (local_44 != (char *)0x0) {
    os_free_mem();
  }
LAB_00278da0:
  FUN_0026cdd0(param_3,param_2,6,uVar3);
  return uVar3;
}

