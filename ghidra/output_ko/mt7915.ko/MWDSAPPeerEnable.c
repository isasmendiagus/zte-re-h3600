// module: mt7915.ko
// function: MWDSAPPeerEnable @ 0x9e8dc
// size: 108 bytes
//

void MWDSAPPeerEnable(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  if ((((*(char *)(param_2 + 0xea) != '\0') && (*(int *)(param_2 + 8) != 0)) &&
      (cVar1 = *(char *)(*(int *)(param_2 + 8) + 0x3f59), cVar1 != '\0')) &&
     (iVar2 = a4_ap_peer_enable(param_1,param_2,1,cVar1,param_4), iVar2 != 0)) {
    return;
  }
  iVar2 = a4_ap_peer_disable(param_1,param_2,1);
  if (iVar2 != 0) {
    *(undefined1 *)(param_2 + 0xea) = 0;
    return;
  }
  return;
}

