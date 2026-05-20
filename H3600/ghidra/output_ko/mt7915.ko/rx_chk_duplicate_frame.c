// module: mt7915.ko
// function: rx_chk_duplicate_frame @ 0xcc60c
// size: 536 bytes
//

undefined4 rx_chk_duplicate_frame(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  bool bVar9;
  
  pbVar8 = *(byte **)(param_2 + 0x1c);
  uVar6 = (uint)*(ushort *)(param_2 + 0x4e);
  uVar7 = (uint)*(ushort *)(param_2 + 0x24);
  iVar1 = HcGetWmmIdx(param_1,param_3);
  if ((*(uint *)(param_2 + 0x44) & 1) != 0) {
    return 0;
  }
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (0x11f < uVar6 || uVar2 <= uVar6) {
    return 0;
  }
  if (param_1 + uVar6 * 0x620 == -0x2f6a0) {
    return 0;
  }
  if ((*pbVar8 & 0x7c) == 0x48) {
    return 0;
  }
  bVar3 = *pbVar8 >> 7 ^ 1;
  uVar2 = (uint)*(byte *)(param_2 + 0x4a) + iVar1 * 4 & 0xff;
  if (0x10 < uVar2) {
    bVar3 = 1;
  }
  if (bVar3 != 0) {
    uVar2 = 0x10;
  }
  if ((*(uint *)(param_2 + 0x44) & 2) == 0) {
    bVar3 = pbVar8[1];
    if (((bVar3 & 8) == 0) ||
       (*(uint *)(param_1 + (uVar2 + uVar6 * 0x188 + 0xbe04) * 4 + 0x1c0) != uVar7)) {
      *(uint *)(param_1 + (uVar2 + uVar6 * 0x188 + 0xbe04) * 4 + 0x1c0) = uVar7;
      return 0;
    }
    goto LAB_000cc744;
  }
  cVar4 = *(char *)(param_2 + 0x73);
  iVar1 = param_1 + (uVar2 + uVar6 * 0x188) * 4;
  uVar5 = *(byte *)(param_1 + uVar6 * 0x620 + uVar2 + 0x2f978) - 2;
  if (uVar7 == (*(uint *)(iVar1 + 0x2f98c) & 0xffff)) {
    bVar9 = uVar5 == 1;
    if (uVar5 < 2) {
      bVar9 = cVar4 == '\x03';
    }
    if (!bVar9) goto LAB_000cc708;
LAB_000cc818:
    *(uint *)(iVar1 + 0x2f9d0) = *(uint *)(iVar1 + 0x2f98c);
    cVar4 = *(char *)(param_2 + 0x73);
  }
  else {
    if (uVar5 < 2) goto LAB_000cc818;
LAB_000cc708:
    if (cVar4 == '\x01') goto LAB_000cc818;
  }
  *(char *)(param_1 + uVar6 * 0x620 + uVar2 + 0x2f978) = cVar4;
  *(uint *)(iVar1 + 0x2f98c) = uVar7;
  bVar3 = pbVar8[1];
  if ((bVar3 & 8) == 0) {
    return 0;
  }
  if (*(uint *)(iVar1 + 0x2f9d0) != uVar7) {
    return 0;
  }
LAB_000cc744:
  if ((*(byte *)(param_2 + 0x22) != 0) &&
     (*(ushort *)(&DAT_002963ba + param_1) != (ushort)*(byte *)(param_2 + 0x22))) {
    return 0;
  }
  if (DebugLevel < 4) {
    return 1;
  }
  printk("%s(): pFrameCtrl->Retry=%d, trEntry->cacheSn[%d]=%d, pkt->sn=%d\n",
         "rx_chk_duplicate_frame",((uint)bVar3 << 0x1c) >> 0x1f,uVar2,
         *(undefined4 *)(param_1 + (uVar6 * 0x188 + uVar2 + 0xbe04) * 4 + 0x1c0),uVar7);
  return 1;
}

