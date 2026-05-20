// module: mt7915.ko
// function: ge_rx_enq_dataq_pkt @ 0xd0c0c
// size: 164 bytes
//

undefined4 ge_rx_enq_dataq_pkt(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = param_1 + 0x285bf0;
  OS_SPIN_LOCK_BH(iVar1);
  if (0xfff < (uint)(*(int *)(param_1 + 0x285c0c) + *(int *)(param_1 + 0x285bfc))) {
    OS_SPIN_UNLOCK_BH(iVar1);
    *(int *)(param_1 + 0x9dcd4) = *(int *)(param_1 + 0x9dcd4) + 1;
    RTMPFreeNdisPacket(param_1,param_2);
    return 1;
  }
  *param_2 = 0;
  if (*(undefined4 **)(param_1 + 0x285bf8) == (undefined4 *)0x0) {
    *(undefined4 **)(param_1 + 0x285bf4) = param_2;
  }
  else {
    **(undefined4 **)(param_1 + 0x285bf8) = param_2;
  }
  *(undefined4 **)(param_1 + 0x285bf8) = param_2;
  *(int *)(param_1 + 0x285bfc) = *(int *)(param_1 + 0x285bfc) + 1;
  OS_SPIN_UNLOCK_BH(iVar1);
  return 0;
}

