// module: mt7915.ko
// function: IGMPSnooping @ 0x240e34
// size: 1076 bytes
//

void IGMPSnooping(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                 undefined2 param_6)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  uint uVar10;
  bool bVar11;
  undefined4 local_40;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  byte local_2b;
  byte local_2a;
  byte local_29;
  
  if (param_5 == 0) {
    return;
  }
  puVar9 = *(undefined4 **)(param_5 + 8);
  if (puVar9 == (undefined4 *)0x0) {
    return;
  }
  iVar3 = isIgmpPkt(param_2,param_4);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = puVar9[5];
  iVar4 = (*(byte *)(param_4 + 2) & 0xf) * 4 + 2;
  iVar7 = param_4 + iVar4;
  bVar1 = *(byte *)(param_4 + iVar4);
  if (iVar3 == 1) {
    if (*(char *)(param_5 + 0xe8) == '\0') {
      local_40 = 1;
    }
    else {
      local_40 = 0x81;
    }
  }
  else {
    local_40 = 1;
  }
  if (DebugLevel < 3) {
    switch(bVar1) {
    case 0x12:
    case 0x16:
      if (iVar7 == -4) goto LAB_002410a0;
      break;
    default:
      goto switchD_00240ec0_caseD_13;
    case 0x17:
      if (iVar7 == -4) goto LAB_00241118;
LAB_002410d8:
      local_2a = *(byte *)(iVar7 + 6);
      local_29 = *(byte *)(iVar7 + 7);
      local_2b = *(byte *)(iVar7 + 5) & 0x7f;
      local_2e = 1;
      local_2d = 0;
      local_2c = 0x5e;
LAB_0024110c:
      if (2 < DebugLevel) {
        printk("EntryDelete IGMP Group=%02x:%02x:%02x:%02x:%02x:%02x\n",local_2e,local_2d,local_2c,
               local_2b,local_2a,local_29);
      }
      iVar3 = puVar9[5];
LAB_00241118:
      if ((iVar3 == 1) && (*(char *)(param_5 + 0xe8) != '\0')) {
        return;
      }
      AsicMcastEntryDelete
                (param_1,&local_2e,*(undefined1 *)((int)puVar9 + 0x999),param_3,*puVar9,param_6);
      return;
    case 0x22:
switchD_00240ec0_caseD_22:
      pbVar8 = (byte *)(iVar7 + 8);
      uVar5 = (*(ushort *)(iVar7 + 6) & 0xff) << 8 | (uint)(*(ushort *)(iVar7 + 6) >> 8);
      if (uVar5 != 0) {
        uVar10 = 0;
        do {
          uVar6 = (*(ushort *)(pbVar8 + 2) & 0xff) << 8 | (uint)(*(ushort *)(pbVar8 + 2) >> 8);
          bVar1 = *pbVar8;
          bVar2 = pbVar8[1];
          if (DebugLevel < 3) {
            if (pbVar8 != (byte *)0xfffffffc) {
LAB_00240fe4:
              local_29 = pbVar8[7];
              local_2a = pbVar8[6];
              local_2b = pbVar8[5] & 0x7f;
              local_2d = 0;
              local_2e = 1;
              local_2c = 0x5e;
              goto LAB_00241018;
            }
          }
          else {
            printk("IGMPv3 Type=%d, ADL=%d, numOfSource=%d\n",bVar1,(uint)bVar2,uVar6);
            if (pbVar8 != (byte *)0xfffffffc) goto LAB_00240fe4;
LAB_00241018:
            if (2 < DebugLevel) {
              printk("IGMP Group=%02x:%02x:%02x:%02x:%02x:%02x\n",local_2e,local_2d,local_2c,
                     local_2b,local_2a,local_29);
            }
          }
          bVar11 = 1 < bVar1;
          if (bVar1 != 2) {
            bVar11 = bVar1 != 4;
          }
          if (bVar11 && (bVar1 != 2 && bVar1 != 5)) {
            if (bVar1 == 6 || (bVar1 & 0xfd) == 1) {
              if (uVar6 != 0) goto LAB_00241030;
              if ((puVar9[5] != 1) || (*(char *)(param_5 + 0xe8) == '\0')) {
                AsicMcastEntryDelete
                          (param_1,&local_2e,*(undefined1 *)((int)puVar9 + 0x999),param_3,*puVar9,
                           param_6);
              }
            }
          }
          else {
LAB_00241030:
            AsicMcastEntryInsert
                      (param_1,&local_2e,*(undefined1 *)((int)puVar9 + 0x999),local_40,param_3,
                       *puVar9,param_6);
          }
          uVar10 = uVar10 + 1;
          pbVar8 = pbVar8 + (uint)bVar2 + (uVar6 + 2) * 4;
        } while (uVar10 != uVar5);
      }
      goto switchD_00240ec0_caseD_13;
    }
LAB_00241064:
    local_2a = *(byte *)(iVar7 + 6);
    local_29 = *(byte *)(iVar7 + 7);
    local_2b = *(byte *)(iVar7 + 5) & 0x7f;
    local_2e = 1;
    local_2d = 0;
    local_2c = 0x5e;
  }
  else {
    printk("IGMP type=%0x\n",bVar1);
    if (bVar1 != 0x16) {
      if (bVar1 < 0x17) {
        if (bVar1 == 0x12) goto LAB_0024129c;
      }
      else {
        if (bVar1 == 0x17) {
          if (iVar7 != -4) goto LAB_002410d8;
          goto LAB_0024110c;
        }
        if (bVar1 == 0x22) goto switchD_00240ec0_caseD_22;
      }
      if (2 < DebugLevel) {
        printk("unknow IGMP Type=%d\n",bVar1);
      }
switchD_00240ec0_caseD_13:
      return;
    }
LAB_0024129c:
    if (iVar7 != -4) goto LAB_00241064;
  }
  if (2 < DebugLevel) {
    printk("EntryInsert IGMP Group=%02x:%02x:%02x:%02x:%02x:%02x\n",local_2e,local_2d,local_2c,
           local_2b,local_2a,local_29);
  }
LAB_002410a0:
  AsicMcastEntryInsert
            (param_1,&local_2e,*(undefined1 *)((int)puVar9 + 0x999),local_40,param_3,*puVar9,param_6
            );
  return;
}

