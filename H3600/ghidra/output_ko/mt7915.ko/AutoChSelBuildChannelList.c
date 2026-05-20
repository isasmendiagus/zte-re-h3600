// module: mt7915.ko
// function: AutoChSelBuildChannelList @ 0x23dd4
// size: 172 bytes
//

void AutoChSelBuildChannelList(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = HcGetBandByWdev(param_3);
  iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,uVar1);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","AutoChSelBuildChannelList");
  }
  os_zero_mem(iVar2 + 0x74,0x1e0);
  if (param_2 == 0) {
    *(undefined1 *)(iVar2 + 0x14) = 0;
    AutoChSelBuildChannelListFor2G(param_1,param_3);
  }
  else {
    *(undefined1 *)(iVar2 + 0x14) = 1;
    AutoChSelBuildChannelListFor5G(param_1,param_3);
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","AutoChSelBuildChannelList");
  return;
}

