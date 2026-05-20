// module: mt7915.ko
// function: PMF_PerformRxFrameAction @ 0x21aca4
// size: 616 bytes
//

undefined1 PMF_PerformRxFrameAction(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  int *piVar6;
  byte *pbVar7;
  bool bVar8;
  
  uVar1 = *(ushort *)(param_2 + 0x4e);
  pbVar7 = *(byte **)(param_2 + 0x1c);
  uVar2 = *(ushort *)(param_2 + 0x48);
  uVar3 = HcGetMaxStaNum();
  bVar8 = uVar1 < uVar3;
  if (bVar8) {
    piVar6 = (int *)((uint)*(ushort *)(param_2 + 0x4e) * 0x14c0 + param_1);
  }
  else {
    piVar6 = (int *)0x0;
  }
  if (bVar8) {
    piVar6 = piVar6 + 0x28748;
  }
  if ((((**(byte **)(param_2 + 0x28) & 1) != 0) && ((*pbVar7 & 0xc) == 0)) &&
     (((*pbVar7 & 0xf0) + 0x60 & 0xd0) == 0)) {
    cVar5 = *(char *)(param_1 + 0x286285);
    if (cVar5 == '\x01') {
      piVar6 = (int *)MacTableLookup(param_1,*(undefined4 *)(param_2 + 0x2c));
      cVar5 = *(char *)(param_1 + 0x286285);
    }
    if (cVar5 == '\0') {
      piVar6 = (int *)MacTableLookup2(param_1,*(undefined4 *)(param_2 + 0x2c));
    }
    if (piVar6 == (int *)0x0) {
      return 1;
    }
    if (*(char *)((int)piVar6 + 0x562) == '\0') {
      return 1;
    }
  }
  iVar4 = PMF_RobustFrameClassify
                    (*(undefined4 *)(param_2 + 0x1c),pbVar7 + 0x18,uVar2 - 0x18,piVar6,1);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if (iVar4 == 3) {
      if (((piVar6 == (int *)0x0) || (*piVar6 != 2)) ||
         ((((*pbVar7 & 0xf0) + 0x60 & 0xd0) != 0 || (*(char *)((int)piVar6 + 0x562) != '\x01')))) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("[PMF]%s: NOT_ROBUST_UNICAST_FRAME, FC->SubType=%d (wcid=%d)\n",
               "PMF_PerformRxFrameAction",*pbVar7 >> 4,*(undefined2 *)(param_2 + 0x4e));
        return 0;
      }
LAB_0021aeac:
      PMF_MlmeSAQueryReq(param_1,piVar6);
      return 0;
    }
    if (iVar4 == 5) {
      *(short *)(param_2 + 0x48) = *(short *)(param_2 + 0x48) + -0x12;
    }
    else if (((iVar4 == 2) && (piVar6 != (int *)0x0)) &&
            ((*piVar6 == 2 && (*(char *)((int)piVar6 + 0x562) == '\x01')))) {
      return 0;
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    if (iVar4 == 2) {
      if ((piVar6 != (int *)0x0) && (*(char *)((int)piVar6 + 0x562) == '\x01')) {
        return 0;
      }
    }
    else if (iVar4 == 3) {
      if ((piVar6 == (int *)0x0 || ((*pbVar7 & 0xf0) + 0x60 & 0xd0) != 0) ||
         (*(char *)((int)piVar6 + 0x562) != '\x01')) {
        if (-1 < DebugLevel) {
          printk("[PMF]%s: NOT_ROBUST_UNICAST_FRAME, FC->SubType=%d\n","PMF_PerformRxFrameAction",
                 *pbVar7 >> 4);
          return 0;
        }
        return 0;
      }
      goto LAB_0021aeac;
    }
  }
  return 1;
}

