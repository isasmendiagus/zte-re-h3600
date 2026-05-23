// module: mt7915.ko
// function: ChannelInfoInit @ 0x1fcb4
// size: 160 bytes
//

void ChannelInfoInit(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  int local_1c;
  
  iVar2 = 0;
  local_1c = 0;
  do {
    piVar1 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,iVar2);
    local_1c = 0;
    os_alloc_mem(param_1,&local_1c,0x514);
    if (local_1c == 0) {
      *piVar1 = 0;
      if (-1 < DebugLevel) {
        printk("%s Fail to alloc memory for pAd->pChannelInfo","ChannelInfoInit");
      }
    }
    else {
      os_zero_mem(local_1c,0x514);
      *piVar1 = local_1c;
    }
    bVar3 = iVar2 != 1;
    iVar2 = 1;
  } while (bVar3);
  return;
}

