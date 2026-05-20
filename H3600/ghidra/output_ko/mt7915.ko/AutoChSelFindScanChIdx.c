// module: mt7915.ko
// function: AutoChSelFindScanChIdx @ 0x24310
// size: 260 bytes
//

int AutoChSelFindScanChIdx(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = HcGetBandByWdev(param_2);
  iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,uVar1);
  if (DebugLevel < 3) {
    if (param_3 == -1) {
      return 0;
    }
    iVar3 = (int)(char)((char)param_3 + '\x01');
    if ((int)(uint)*(byte *)(iVar2 + 0xe) <= iVar3) {
      return -1;
    }
  }
  else {
    printk("%s----------------->\n","AutoChSelFindScanChIdx");
    if (param_3 == -1) {
      iVar3 = 0;
    }
    else {
      iVar3 = (int)(char)((char)param_3 + '\x01');
      if ((int)(uint)*(byte *)(iVar2 + 0xe) <= iVar3) {
        iVar3 = -1;
      }
    }
  }
  if ((2 < DebugLevel) &&
     (printk("%s : BandIdx = %d, LastScanChIdx = %d, ScanChIdx = %d, ChannelListNum = %d\n",
             "AutoChSelFindScanChIdx",uVar1,param_3,iVar3,*(undefined1 *)(iVar2 + 0xe)),
     2 < DebugLevel)) {
    printk("%s<-----------------\n","AutoChSelFindScanChIdx");
  }
  return iVar3;
}

