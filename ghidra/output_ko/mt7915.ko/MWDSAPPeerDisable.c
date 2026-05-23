// module: mt7915.ko
// function: MWDSAPPeerDisable @ 0x9e948
// size: 32 bytes
//

void MWDSAPPeerDisable(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = a4_ap_peer_disable(param_1,param_2,1);
  if (iVar1 != 0) {
    *(undefined1 *)(param_2 + 0xea) = 0;
  }
  return;
}

