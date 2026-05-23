// module: mt7915.ko
// function: ApSiteSurveyNew_by_wdev @ 0x144a64
// size: 380 bytes
//

undefined4
ApSiteSurveyNew_by_wdev
          (int param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5,
          undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined1 local_5c;
  undefined1 auStack_51 [6];
  undefined1 local_4b;
  undefined1 local_4a;
  
  uVar2 = get_scan_tab_by_wdev(param_1,param_6);
  iVar3 = get_scan_ctrl_by_wdev(param_1,param_6);
  iVar4 = HcGetBandByWdev(param_6);
  RTMPZeroMemory(auStack_51,0x29);
  AsicDisableSync(param_1,0);
  if (3 < DebugLevel) {
    printk("%s , %u, %u, %u","ApSiteSurveyNew_by_wdev",param_2,param_3,param_4);
  }
  BssTableInit(uVar2);
  ChannelInfoResetNew(param_1,iVar4);
  *(undefined1 *)(iVar3 + 0x54) = 0;
  iVar1 = DebugLevel;
  bVar5 = *(char *)(iVar3 + 0x4f) == '\0';
  if (bVar5) {
    *(char *)(iVar3 + 0x4a) = (char)param_2;
  }
  local_4b = 2;
  local_4a = (undefined1)param_4;
  if (bVar5) {
    local_5c = (undefined1)param_3;
    *(undefined1 *)(iVar3 + 0x4f) = local_5c;
  }
  (&DAT_0036b824)[param_1 + iVar4] = param_5;
  *(char *)(param_1 + 0x28608c) = (char)iVar4;
  if (0 < iVar1) {
    printk("%s : bandidx :%d!! \n","ApSiteSurveyNew_by_wdev",iVar4);
  }
  if (param_2 != 0) {
    uVar2 = Channel2Index(param_1,param_2 & 0xff,iVar4);
    iVar3 = DebugLevel;
    (&DAT_0036b861)[param_1] = (char)uVar2;
    if (2 < iVar3) {
      printk("[%s] ApCfg.current_channel_index = %d\n","ApSiteSurveyNew_by_wdev",uVar2);
    }
    *(uint *)(param_1 + 0x286074) = param_2;
  }
  cntl_scan_request(param_6,auStack_51);
  return 1;
}

