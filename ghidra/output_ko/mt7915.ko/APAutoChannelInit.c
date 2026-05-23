// module: mt7915.ko
// function: APAutoChannelInit @ 0x22cf0
// size: 328 bytes
//

void APAutoChannelInit(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = HcGetBandByWdev(param_2);
  iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,iVar1);
  if (*(int *)(iVar2 + 4) == 0) {
    if (-1 < DebugLevel) {
      printk("pAutoChCtrl->pBssInfoTab equal NULL.\n");
    }
  }
  else {
    __memzero(*(int *)(iVar2 + 4),0x2a01);
  }
  piVar3 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,iVar1);
  if (*piVar3 == 0) {
    if (-1 < DebugLevel) {
      printk("pChannelInfo equal NULL, band:%d\n",iVar1);
    }
  }
  else {
    __memzero(*piVar3,0x514);
  }
  CheckPhyModeIsABand(param_1,iVar1);
  (&DAT_0036b861)[param_1] = 0;
  AsicGetChBusyCnt(param_1,iVar1,0,0);
  if (iVar1 != 0) {
    if (iVar1 != 1) {
      return;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83092004,0);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83092004,0xa00);
    return;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83082004,0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83082004,0xa00);
  return;
}

