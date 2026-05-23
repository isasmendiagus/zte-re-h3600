// module: mt7915.ko
// function: PeerRMAction @ 0xa1cb4
// size: 228 bytes
//

void PeerRMAction(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_2 + 0x19);
  uVar2 = *(ushort *)(param_2 + 0x920);
  uVar3 = HcGetMaxStaNum();
  if (uVar3 <= uVar2) {
    return;
  }
  iVar4 = *(int *)((uint)*(ushort *)(param_2 + 0x920) * 0x14c0 + param_1 + 0xa1d28);
  if (iVar4 == 0) {
    return;
  }
  if (*(char *)(iVar4 + 0xb21) != '\x01') {
    return;
  }
  if (cVar1 != '\x01') {
    if (cVar1 == '\0') {
      if (2 < DebugLevel) {
        printk("%s: Get RRM Measure request.\n","PeerRMAction");
      }
      RRM_PeerMeasureReqAction(param_1,param_2);
      return;
    }
    if (cVar1 != '\x04') {
      return;
    }
    RRM_PeerNeighborReqAction(param_1,param_2);
    return;
  }
  if (2 < DebugLevel) {
    printk("%s: Get RRM Measure report.\n","PeerRMAction");
  }
  RRM_PeerMeasureRepAction(param_1,param_2);
  return;
}

