// module: mt7915.ko
// function: wlan_operate_update_ht_cap @ 0x108080
// size: 432 bytes
//

void wlan_operate_update_ht_cap
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  
  iVar11 = *(int *)(param_1 + 8);
  iVar9 = *(int *)(param_1 + 0xb10);
  iVar8 = *(int *)(param_1 + 0xb14);
  iVar5 = hc_get_chip_cap(*(undefined4 *)(iVar11 + 0xa797a0));
  if (param_1 == 0) {
    iVar10 = 0;
  }
  else {
    iVar10 = *(int *)(param_1 + 0xb14);
    if (iVar10 != 0) {
      iVar10 = iVar10 + 0x36;
    }
  }
  if (iVar8 == 0 || iVar9 == 0) {
    return;
  }
  bVar3 = *(byte *)(iVar9 + 0x17);
  bVar4 = *(byte *)(iVar8 + 0x36);
  *(byte *)(iVar8 + 0xb) = bVar3;
  bVar3 = bVar3 & 1;
  *(byte *)(iVar8 + 0x36) = bVar4 & 0xfe | bVar3;
  *(byte *)(iVar8 + 0x36) = bVar4 & 0xfc | bVar3 | (*(byte *)(iVar9 + 0x15) & 1) << 1;
  uVar6 = (uint)*(byte *)(iVar9 + 0x15);
  bVar12 = *(char *)(iVar9 + 0x18) == '\x01';
  bVar3 = *(byte *)(iVar8 + 0x36);
  if (bVar12) {
    uVar6 = uVar6 - 1;
  }
  *(char *)(iVar8 + 0xc) = *(char *)(iVar9 + 0x18);
  bVar4 = bVar12 << 5;
  bVar1 = (bVar12 && uVar6 == 0) << 6;
  *(byte *)(iVar8 + 0x36) = bVar3 & 0x9f | bVar4 | bVar1;
  bVar2 = (*(byte *)(iVar9 + 0x1b) & 1) << 4;
  *(byte *)(iVar8 + 0x36) = bVar3 & 0x8f | bVar4 | bVar1 | bVar2;
  *(byte *)(iVar8 + 0x38) = *(byte *)(iVar8 + 0x38) & 0xe3 | (*(byte *)(iVar9 + 0x2c) & 7) << 2;
  *(byte *)(iVar8 + 0x36) =
       bVar3 & 0x83 | bVar4 | bVar1 | bVar2 | (*(byte *)(iVar9 + 0x2e) & 3) << 2;
  wlan_operate_update_ht_stbc(param_1,*(undefined1 *)(iVar9 + 0x16));
  operate_loader_trx_stream(param_1,iVar8,*(undefined1 *)(iVar9 + 3),*(undefined1 *)(iVar9 + 4));
  *(byte *)(iVar8 + 0x37) = *(byte *)(iVar8 + 0x37) & 0xf7 | (*(char *)(iVar5 + 0x5e) != '\0') << 3;
  *(byte *)(iVar8 + 0x38) = *(byte *)(iVar8 + 0x38) & 0xfc | *(byte *)(iVar5 + 0x5f) & 3;
  if ((param_1 != 0) && (iVar7 = *(int *)(param_1 + 0xb14), iVar7 != 0)) {
    *(byte *)(iVar7 + 0x37) = *(byte *)(iVar7 + 0x37) & 0xfb;
    iVar7 = *(int *)(param_1 + 0xb14);
    if (iVar7 != 0) {
      *(undefined1 *)(iVar7 + 0x1c) = 0;
      *(byte *)(iVar7 + 0x37) = *(byte *)(iVar7 + 0x37) & 0x7f;
      iVar7 = *(int *)(param_1 + 0xb14);
      if (iVar7 != 0) {
        *(byte *)(iVar7 + 0x37) = *(byte *)(iVar7 + 0x37) & 0xdf;
      }
    }
  }
  bVar12 = *(byte *)(param_1 + 0x1a) == 0xd;
  if (*(byte *)(param_1 + 0x1a) < 0xe) {
    bVar12 = *(char *)(iVar9 + 0x15) == '\x01';
  }
  *(byte *)(iVar8 + 0x37) = *(byte *)(iVar8 + 0x37) & 0xef | bVar12 << 4;
  if (*(char *)(iVar5 + 0x96) != '\0') {
    mt_WrapSetETxBFCap(iVar11,param_1,iVar10 + 0x15,param_4);
    return;
  }
  return;
}

