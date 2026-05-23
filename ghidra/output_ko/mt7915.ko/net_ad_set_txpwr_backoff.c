// module: mt7915.ko
// function: net_ad_set_txpwr_backoff @ 0x25cd4c
// size: 68 bytes
//

undefined4 net_ad_set_txpwr_backoff(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  iVar1 = MtCmdTxBfBackoffCtrl(iVar1,param_2,param_3);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x601;
  }
  return uVar2;
}

