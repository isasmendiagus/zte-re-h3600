// module: mt7915.ko
// function: PeerPairMsg3Action @ 0x120974
// size: 780 bytes
//

void PeerPairMsg3Action(int param_1,int param_2,uint *param_3,int param_4)

{
  uint uVar1;
  uint *puVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint *puVar12;
  bool bVar13;
  undefined1 auStack_3c [24];
  
  log_time_begin(1,auStack_3c);
  uVar10 = *param_3;
  if (2 < DebugLevel) {
    printk("===> %s\n","PeerPairMsg3Action");
  }
  if ((*(byte *)(param_4 + 1) & 3) == 3) {
    iVar8 = 0x1e;
    uVar5 = 0x89;
  }
  else {
    iVar8 = 0x18;
    uVar5 = 0x83;
  }
  if (*(uint *)(param_4 + 0x908) < uVar5) {
    return;
  }
  iVar9 = param_4 + iVar8 + 8;
  iVar8 = WpaMessageSanity(param_1,iVar9,(*(uint *)(param_4 + 0x908) - 8) - iVar8,3,param_3,param_2,
                           (int)param_3 + 0x1ce);
  if (iVar8 == 0) {
    return;
  }
  bVar13 = (uVar10 & 0x18) != 0;
  if (*(char *)((int)param_3 + 0x3d9) == '\x01') {
    if (bVar13) goto LAB_00120a48;
    uVar10 = (uint)*(byte *)(param_2 + 0x91e);
    pbVar6 = (byte *)(iVar9 + 0x40);
    iVar11 = param_2 + uVar10 * 8;
    puVar12 = (uint *)(iVar11 + 0x1440);
    uVar7 = 0;
    iVar8 = 0;
    uVar5 = 0;
    *puVar12 = 0;
    *(undefined4 *)(iVar11 + 0x1444) = 0;
    do {
      pbVar6 = pbVar6 + 1;
      bVar3 = *pbVar6;
      uVar1 = (uint)bVar3 << (uVar5 & 0xff);
      bVar13 = CARRY4(uVar7,uVar1);
      uVar7 = uVar7 + uVar1;
      iVar8 = iVar8 + ((uint)bVar3 << (uVar5 - 0x20 & 0xff) | (uint)(bVar3 >> (0x20 - uVar5 & 0xff))
                      ) + (uint)bVar13;
      uVar5 = uVar5 + 8;
      *puVar12 = uVar7;
      *(int *)(iVar11 + 0x1444) = iVar8;
      iVar4 = DebugLevel;
    } while (pbVar6 != (byte *)(iVar9 + 0x46));
    *(undefined1 *)(param_2 + uVar10 + 0x1460) = 0;
    *(undefined1 *)(param_2 + 0x1464) = 0;
    if (0 < iVar4) {
      printk("%s(%d): update CCMP_BC_PN to %llu\n","PeerPairMsg3Action",
             *(undefined2 *)(param_2 + 0xe0),iVar8,uVar7,iVar8);
    }
    if (((&DAT_0036790d)[param_1] == '\x01') &&
       (iVar8 = MacTableLookup(param_1,param_4 + 10), iVar8 != 0)) {
      uVar5 = *(uint *)(iVar11 + 0x1444);
      puVar2 = (uint *)(iVar8 + (uVar10 + 0x288) * 8);
      *puVar2 = *puVar12;
      puVar2[1] = uVar5;
      *(undefined1 *)(iVar8 + uVar10 + 0x1460) = *(undefined1 *)(param_2 + uVar10 + 0x1460);
      *(undefined1 *)(iVar8 + 0x1464) = *(undefined1 *)(param_2 + 0x1464);
    }
  }
  else if (bVar13) goto LAB_00120a48;
  WLAN_EXTENDER_Report_LinkUpDown_Event(param_1,*(undefined4 *)(param_2 + 8),0xa427);
LAB_00120a48:
  bVar3 = *(byte *)(param_2 + 0x12f8);
  if ((bVar3 & 8) == 0) {
    *(undefined4 *)(param_1 + 0xa7cc00) = 0xffffffff;
  }
  else if ((bVar3 & 7) != 0) {
    *(uint *)(param_1 + 0xa7cc00) = (bVar3 & 7) - 1;
  }
  if (-1 < DebugLevel) {
    printk("(%s): set max hopnum %d \n","PeerPairMsg3Action",*(undefined4 *)(param_1 + 0xa7cc00));
  }
  memmove(param_3 + 0xe4,(void *)(iVar9 + 9),8);
  iVar8 = memcmp(param_3 + 0xcc,(void *)(iVar9 + 0x11),0x20);
  if (iVar8 == 0) {
    *(byte *)((int)param_3 + 0x595) = (byte)(((uint)*(byte *)(param_4 + 1) << 0x19) >> 0x1f);
    WPABuildPairMsg4(param_1,param_3,param_2);
    log_time_end(2,"peer_msg3",1,auStack_3c);
  }
  return;
}

