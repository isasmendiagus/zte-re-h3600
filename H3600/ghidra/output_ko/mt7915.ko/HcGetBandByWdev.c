// module: mt7915.ko
// function: HcGetBandByWdev @ 0xa8c48
// size: 124 bytes
//

uint HcGetBandByWdev(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar4 = *(int *)(param_1 + 0xabc);
  iVar3 = *(int *)(param_1 + 8);
  iVar1 = hdev_obj_state_ready(iVar4);
  if ((iVar1 != 0) && (*(int *)(iVar4 + 8) != 0)) {
    uVar2 = RcGetBandIdx();
    return uVar2;
  }
  if ((iVar3 != 0) && (*(char *)(iVar3 + 0x79504d) != '\0')) {
    return (uint)((*(ushort *)(param_1 + 0x18) & 0xb1) != 0);
  }
  return 0;
}

