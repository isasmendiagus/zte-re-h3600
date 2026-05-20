// module: mt7915.ko
// function: AutoChSelScanStart @ 0x264c0
// size: 16 bytes
//

void AutoChSelScanStart(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  
  if (param_2 == 0 || param_1 == 0) {
    return;
  }
  iVar1 = HcGetBandByWdev(param_2);
  iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,iVar1);
  iVar3 = scan_in_run_state(param_1,param_2);
  if (iVar3 == 0) {
    *(undefined4 *)(iVar2 + 0x10) = 0;
    os_zero_mem(iVar2 + 0x74,0x1e0);
    if (2 < DebugLevel) {
      printk("%s----------------->\n","AutoChSelScanStart");
    }
    *(undefined1 *)(param_1 + 0xa7c349) = 0;
    *(undefined1 *)(param_1 + iVar1 + 0xa7c304) = 0;
    *(undefined1 *)(iVar2 + 0xc) = 0;
    *(int *)(iVar2 + 8) = param_2;
    bVar5 = (*(ushort *)(param_2 + 0x18) & 0xb1) == 0;
    if (bVar5) {
      *(byte *)(iVar2 + 0x14) = (byte)*(ushort *)(param_2 + 0x18) & 0xb1;
    }
    else {
      *(undefined1 *)(iVar2 + 0x14) = 1;
    }
    AutoChSelBuildChannelList(param_1,!bVar5,param_2);
    if (0 < DebugLevel) {
      printk("%s: IsABand = %d, ChannelListNum = %d\n","AutoChSelScanStart",
             *(undefined1 *)(iVar2 + 0x14),*(undefined1 *)(iVar2 + 0xe));
    }
    MlmeEnqueueWithWdev(param_1,0x2e,0,0,0,*(undefined1 *)(param_2 + 0xe),param_2);
    RtmpOsMlmeUp(param_1 + 0x286298);
    if (2 < DebugLevel) {
      pcVar4 = "%s<-----------------\n";
      goto LAB_000242c0;
    }
  }
  else if (-1 < DebugLevel) {
    pcVar4 = "%s::Failed!!!Scan is running, please try again after scan done!\n";
LAB_000242c0:
    printk(pcVar4,"AutoChSelScanStart");
    return;
  }
  return;
}

