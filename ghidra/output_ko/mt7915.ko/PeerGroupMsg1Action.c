// module: mt7915.ko
// function: PeerGroupMsg1Action @ 0x12120c
// size: 664 bytes
//

void PeerGroupMsg1Action(int param_1,int param_2,uint param_3,int param_4)

{
  uint uVar1;
  uint *puVar2;
  byte bVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint *puVar13;
  bool bVar14;
  uint uVar15;
  int iVar16;
  
  if (2 < DebugLevel) {
    printk("===> %s\n","PeerGroupMsg1Action");
  }
  bVar14 = (*(byte *)(param_4 + 1) & 3) != 3;
  if (bVar14) {
    iVar8 = 0x20;
  }
  else {
    iVar8 = 0x26;
  }
  iVar8 = param_4 + iVar8;
  if (bVar14) {
    iVar6 = 0x18;
  }
  else {
    iVar6 = 0x1e;
  }
  uVar15 = param_3;
  iVar16 = param_2;
  iVar6 = WpaMessageSanity(param_1,iVar8,(*(int *)(param_4 + 0x908) + -8) - iVar6,5,param_3,param_2,
                           param_3 + 0x1ce);
  if (iVar6 == 0) {
    return;
  }
  if (*(char *)(param_2 + 0x1464) == '\x01') {
    uVar10 = (uint)*(byte *)(param_2 + 0x91e);
    pbVar5 = (byte *)(iVar8 + 0x40);
    iVar11 = param_2 + uVar10 * 8;
    puVar13 = (uint *)(iVar11 + 0x1440);
    uVar12 = 0;
    uVar9 = 0;
    iVar6 = 0;
    *puVar13 = 0;
    *(undefined4 *)(iVar11 + 0x1444) = 0;
    do {
      pbVar5 = pbVar5 + 1;
      bVar3 = *pbVar5;
      uVar1 = (uint)bVar3 << (uVar12 & 0xff);
      bVar14 = CARRY4(uVar9,uVar1);
      uVar9 = uVar9 + uVar1;
      iVar6 = iVar6 + ((uint)bVar3 << (uVar12 - 0x20 & 0xff) |
                      (uint)(bVar3 >> (0x20 - uVar12 & 0xff))) + (uint)bVar14;
      uVar12 = uVar12 + 8;
      *puVar13 = uVar9;
      *(int *)(iVar11 + 0x1444) = iVar6;
      iVar4 = DebugLevel;
    } while (pbVar5 != (byte *)(iVar8 + 0x46));
    iVar7 = param_2 + uVar10;
    *(undefined1 *)(iVar7 + 0x1460) = 0;
    *(undefined1 *)(param_2 + 0x1464) = 0;
    if (0 < iVar4) {
      printk("%s(%d): update CCMP_BC_PN to %llu\n","PeerGroupMsg1Action",
             *(undefined2 *)(param_2 + 0xe0),iVar7,uVar9,iVar6);
      uVar15 = uVar9;
      iVar16 = iVar6;
    }
    if (((&DAT_0036790d)[param_1] == '\x01') &&
       (iVar6 = MacTableLookup(param_1,param_4 + 10), iVar6 != 0)) {
      uVar9 = *(uint *)(iVar11 + 0x1444);
      puVar2 = (uint *)(iVar6 + (uVar10 + 0x288) * 8);
      *puVar2 = *puVar13;
      puVar2[1] = uVar9;
      *(undefined1 *)(iVar6 + uVar10 + 0x1460) = *(undefined1 *)(iVar7 + 0x1460);
      *(undefined1 *)(iVar6 + 0x1464) = *(undefined1 *)(param_2 + 0x1464);
    }
  }
  WLAN_EXTENDER_Report_LinkUpDown_Event(param_1,*(undefined4 *)(param_2 + 8),0xa427);
  bVar3 = *(byte *)(param_2 + 0x12f8);
  if ((bVar3 & 8) == 0) {
    *(undefined4 *)(param_1 + 0xa7cc00) = 0xffffffff;
  }
  else if ((bVar3 & 7) != 0) {
    *(uint *)(param_1 + 0xa7cc00) = (bVar3 & 7) - 1;
  }
  if (-1 < DebugLevel) {
    printk("(%s): set max hopnum %d \n","PeerGroupMsg1Action",*(undefined4 *)(param_1 + 0xa7cc00),
           param_1 + 0xa7c000,uVar15,iVar16);
  }
  memmove((void *)(param_3 + 0x390),(void *)(iVar8 + 9),8);
  WPABuildGroupMsg2(param_1,param_3,param_2);
  return;
}

