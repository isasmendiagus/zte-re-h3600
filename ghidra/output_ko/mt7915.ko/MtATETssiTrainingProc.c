// module: mt7915.ko
// function: MtATETssiTrainingProc @ 0x28b98c
// size: 792 bytes
//

undefined4 MtATETssiTrainingProc(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  
  iVar7 = *(int *)(param_1 + 0xa39fd4);
  if ((((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) &&
      (param_2 == 6 || param_2 == 3)) && (MtEPAcheck(), *(char *)(param_1 + 0x285a2c) == '\0')) {
    iVar5 = net_ad_wrap_service(param_1);
    param_3 = param_3 * 0xd18;
    uVar1 = *(undefined1 *)(iVar5 + param_3 + 0x1137);
    iVar5 = net_ad_wrap_service(param_1);
    uVar2 = *(undefined1 *)(iVar5 + param_3 + 0x1135);
    iVar5 = net_ad_wrap_service(param_1);
    uVar3 = *(undefined1 *)(iVar5 + param_3 + 0x1138);
    iVar5 = net_ad_wrap_service(param_1);
    uVar4 = *(undefined1 *)(iVar5 + param_3 + 0x1139);
    iVar5 = net_ad_wrap_service(param_1);
    uVar6 = *(undefined4 *)(iVar5 + param_3 + 0x6dc);
    MtATETSSITracking(param_1,1);
    MtATEFCBWCfg(param_1,1);
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1137) = 2;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1135) = 4;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1138) = 9;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1139) = 4;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined4 *)(iVar5 + param_3 + 0x6dc) = 100;
    (**(code **)(iVar7 + 8))(param_1);
    (**(code **)(iVar7 + 0x10))(param_1);
    RtmpOsMsDelay(0x19);
    (**(code **)(iVar7 + 0x18))(param_1);
    (**(code **)(iVar7 + 0xc))(param_1);
    MtTSSICompBackup(param_1,1);
    MtATEFCBWCfg(param_1,0);
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1137) = 3;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1135) = 4;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1138) = 9;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar5 + param_3 + 0x1139) = 2;
    iVar5 = net_ad_wrap_service(param_1);
    *(undefined4 *)(iVar5 + param_3 + 0x6dc) = 100;
    (**(code **)(iVar7 + 8))(param_1);
    (**(code **)(iVar7 + 0x10))(param_1);
    RtmpOsMsDelay(0x19);
    (**(code **)(iVar7 + 0x18))(param_1);
    (**(code **)(iVar7 + 0xc))(param_1);
    MtTSSICompBackup(param_1,0);
    MtTSSICompCfg(param_1);
    MtATETSSITracking(param_1,0);
    MtATEFCBWCfg(param_1,1);
    iVar7 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar7 + param_3 + 0x1137) = uVar1;
    iVar7 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar7 + param_3 + 0x1135) = uVar2;
    iVar7 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar7 + param_3 + 0x1138) = uVar3;
    iVar7 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar7 + param_3 + 0x1139) = uVar4;
    iVar5 = net_ad_wrap_service(param_1);
    iVar7 = DebugLevel;
    *(undefined4 *)(iVar5 + param_3 + 0x6dc) = uVar6;
    if (0 < iVar7) {
      printk("%s: TSSI Training Done!!\n","MtATETssiTrainingProc");
    }
  }
  return 0;
}

