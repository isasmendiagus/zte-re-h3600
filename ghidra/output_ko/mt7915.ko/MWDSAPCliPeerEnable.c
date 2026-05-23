// module: mt7915.ko
// function: MWDSAPCliPeerEnable @ 0x9e968
// size: 168 bytes
//

void MWDSAPCliPeerEnable(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (1 < DebugLevel) {
    printk("%s() peer %d, apcli %d\n","MWDSAPCliPeerEnable",*(undefined1 *)(param_2 + 0x2123e8),
           *(undefined1 *)(param_2 + 0x3f59));
  }
  if (((*(char *)(param_2 + 0x2123e8) != '\0') && (*(char *)(param_2 + 0x3f59) != '\0')) &&
     (iVar1 = a4_apcli_peer_enable(param_1,param_2,param_3,1), iVar1 != 0)) {
    return;
  }
  a4_apcli_peer_disable(param_1,param_2,param_3,1);
  return;
}

