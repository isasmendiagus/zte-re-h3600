// module: mt7915.ko
// function: AsicDMASchedulerInit @ 0x13467c
// size: 48 bytes
//

void AsicDMASchedulerInit(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 2) {
    return;
  }
  AsicNotSupportFunc(param_1,"AsicDMASchedulerInit");
  return;
}

