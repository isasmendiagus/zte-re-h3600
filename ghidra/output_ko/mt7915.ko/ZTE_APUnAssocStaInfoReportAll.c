// module: mt7915.ko
// function: ZTE_APUnAssocStaInfoReportAll @ 0x1613bc
// size: 560 bytes
//

undefined4 ZTE_APUnAssocStaInfoReportAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  uint uVar6;
  int *__s1;
  int iVar7;
  int iVar8;
  int iVar9;
  int *__s2;
  int iVar10;
  int iVar11;
  undefined1 auStack_2b4 [10];
  undefined1 local_2aa;
  int local_2a8;
  int local_2a4 [3];
  undefined1 local_298 [628];
  
  memset(auStack_2b4,0,0x28c);
  if ((param_1 == (int *)0x0) ||
     (iVar3 = get_wdev_by_ioctl_idx_and_iftype
                        (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38)),
     iVar3 == 0)) {
    return 0;
  }
  if (param_1[(int)("MtCmdUpdateProtect" + param_2 * 0x181)] != 0) {
    uVar6 = 0;
    puVar5 = (undefined1 *)((int)param_1 + param_2 * 0x604 + 0xa7d733);
    do {
      puVar5 = puVar5 + 1;
      *puVar5 = 0;
      uVar6 = uVar6 + 1;
    } while (uVar6 < (uint)param_1[(int)("MtCmdUpdateProtect" + param_2 * 0x181)]);
  }
  iVar10 = param_1[(int)("MtCmdGetCfgOnOff" + param_2 * 0x32 + 4)];
  if (iVar10 == 0) {
    return 1;
  }
  iVar8 = 0;
  __s1 = param_1 + (int)("MtCmdGetCfgOnOff" + param_2 * 0x32 + 5);
  iVar9 = 0;
  do {
    iVar7 = param_1[(int)("MtCmdUpdateProtect" + param_2 * 0x181)];
    if (iVar7 != 0) {
      iVar11 = 0;
      __s2 = param_1 + (int)("MtCmdSetSnifferMode" + param_2 * 0x181 + 1);
      do {
        iVar4 = memcmp(__s1,__s2,6);
        if (iVar4 == 0) {
          iVar7 = iVar8 * 0x14;
          iVar11 = iVar11 + param_2 * 0x604;
          iVar4 = __s2[1];
          local_2a4[iVar8 * 5 + -1] = *__s2;
          cVar2 = *(char *)((int)param_1 + iVar11 + 0xa7d3b4);
          *(short *)(local_2a4 + iVar8 * 5) = (short)iVar4;
          iVar8 = iVar8 + 1;
          *(int *)(local_298 + iVar7 + -4) = (int)cVar2;
          uVar1 = *(undefined1 *)(iVar3 + 0x1a);
          *(undefined1 *)((int)param_1 + iVar11 + 0xa7d734) = 1;
          local_298[iVar7] = uVar1;
          break;
        }
        iVar11 = iVar11 + 1;
        __s2 = (int *)((int)__s2 + 6);
      } while (iVar11 != iVar7);
    }
    iVar9 = iVar9 + 1;
    if (iVar9 == iVar10) {
      if (iVar8 == 0) {
        return 1;
      }
      goto LAB_00161598;
    }
    __s1 = (int *)((int)__s1 + 6);
    if (0x1f < iVar8) {
LAB_00161598:
      local_2aa = (undefined1)iVar8;
      Kernel_ASEND("multiapd.map.slave",0xa2bb,auStack_2b4,0x28c,0,0);
      return 1;
    }
  } while( true );
}

