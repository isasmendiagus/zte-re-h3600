// module: mt7915.ko
// function: ZTE_APUnAssocStaInfoRecordAndReport @ 0x1615ec
// size: 1044 bytes
//

undefined4
ZTE_APUnAssocStaInfoRecordAndReport
          (int param_1,undefined4 *param_2,int param_3,int param_4,byte param_5)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  void *pvVar9;
  uint uVar10;
  bool bVar11;
  undefined1 auStack_2b4 [10];
  undefined1 local_2aa;
  undefined4 local_2a8;
  undefined2 local_2a4;
  int local_29c;
  byte local_298;
  
  memset(auStack_2b4,0,0x28c);
  if (param_3 < -0x55 || (param_2 == (undefined4 *)0x0 || param_1 == 0)) {
    return 0;
  }
  iVar3 = memcmp(param_2,&ZERO_MAC_ADDR,6);
  if (iVar3 == 0) {
    return 0;
  }
  bVar11 = param_5 == 0x23;
  if (param_5 < 0x24) {
    bVar11 = param_4 == 1;
  }
  if (bVar11) {
    return 0;
  }
  if (0xe < param_5 && param_4 == 0) {
    return 0;
  }
  uVar10 = *(uint *)(param_1 + param_4 * 0x604 + 0xa7d3b0);
  uVar1 = (undefined1)param_3;
  if (uVar10 != 0) {
    uVar8 = 0;
    pvVar9 = (void *)(param_1 + param_4 * 0x604 + 0xa7d434);
    do {
      iVar3 = memcmp(pvVar9,param_2,6);
      if (iVar3 == 0) {
        *(undefined4 *)
         (param_1 + (int)("MtCmdFwDecompressStart" + param_4 * 0x181 + uVar8 + 0x14) * 4 + 4) =
             jiffies;
        *(undefined1 *)(param_1 + param_4 * 0x604 + uVar8 + 0xa7d3b4) = uVar1;
        goto LAB_00161740;
      }
      uVar8 = uVar8 + 1;
      pvVar9 = (void *)((int)pvVar9 + 6);
    } while (uVar8 != uVar10);
    if (0x7f < uVar8) {
      uVar8 = 0;
      uVar10 = 1;
      piVar5 = (int *)(param_1 + param_4 * 0x604 + 0xa7d7b4);
      do {
        piVar5 = piVar5 + 1;
        if (-1 < *(int *)(param_1 + (int)("MtCmdFwDecompressStart" + param_4 * 0x181 + uVar8 + 0x14)
                                    * 4 + 4) - *piVar5) {
          uVar8 = uVar10;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 != 0x80);
      iVar3 = param_1 + param_4 * 0x604 + uVar8;
      iVar6 = param_1 + param_4 * 0x604 + uVar8 * 6 + 0xa7d430;
      *(undefined1 *)(iVar3 + 0xa7d3b4) = uVar1;
      *(undefined4 *)(iVar6 + 4) = *param_2;
      uVar2 = jiffies;
      *(undefined2 *)(iVar6 + 8) = *(undefined2 *)(param_2 + 1);
      *(undefined4 *)
       (param_1 + (int)("MtCmdFwDecompressStart" + param_4 * 0x181 + uVar8 + 0x14) * 4 + 4) = uVar2;
      *(undefined1 *)(iVar3 + 0xa7d734) = 0;
      goto LAB_00161740;
    }
  }
  iVar6 = param_1 + param_4 * 0x604;
  *(undefined1 *)(iVar6 + uVar10 + 0xa7d3b4) = uVar1;
  iVar3 = param_1 + param_4 * 0x604 + *(int *)(iVar6 + 0xa7d3b0) * 6 + 0xa7d430;
  *(undefined4 *)(iVar3 + 4) = *param_2;
  uVar2 = jiffies;
  *(undefined2 *)(iVar3 + 8) = *(undefined2 *)(param_2 + 1);
  *(undefined4 *)
   (param_1 + (int)("MtCmdFwDecompressStart" + param_4 * 0x181 + *(int *)(iVar6 + 0xa7d3b0) + 0x14)
              * 4 + 4) = uVar2;
  *(undefined1 *)(iVar6 + *(int *)(iVar6 + 0xa7d3b0) + 0xa7d734) = 0;
  uVar8 = *(uint *)(iVar6 + 0xa7d3b0);
  *(uint *)(iVar6 + 0xa7d3b0) = uVar8 + 1;
LAB_00161740:
  iVar3 = *(int *)(param_1 + param_4 * 200 + 0xa7d220);
  if (iVar3 != 0) {
    iVar6 = param_1 + param_4 * 0x604 + uVar8;
    pvVar9 = (void *)(param_4 * 200 + param_1 + 0xa7d224);
    iVar7 = 0;
    do {
      iVar7 = iVar7 + 1;
      iVar4 = memcmp(pvVar9,param_2,6);
      pvVar9 = (void *)((int)pvVar9 + 6);
      if ((iVar4 == 0) && (*(char *)(iVar6 + 0xa7d734) == '\0')) {
        local_2a8 = *param_2;
        local_2a4 = *(undefined2 *)(param_2 + 1);
        local_29c = (int)*(char *)(iVar6 + 0xa7d3b4);
        local_298 = param_5;
        local_2aa = 1;
        Kernel_ASEND("multiapd.map.slave",0xa2bb,auStack_2b4,0x28c,0,0);
        *(undefined1 *)(param_1 + param_4 * 0x604 + uVar8 + 0xa7d734) = 1;
        return 1;
      }
    } while (iVar7 != iVar3);
  }
  return 1;
}

