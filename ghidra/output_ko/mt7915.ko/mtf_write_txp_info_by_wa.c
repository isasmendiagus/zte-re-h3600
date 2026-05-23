// module: mt7915.ko
// function: mtf_write_txp_info_by_wa @ 0x19e878
// size: 728 bytes
//

undefined4 mtf_write_txp_info_by_wa(int param_1,ushort *param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  ushort *puVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  undefined1 uVar11;
  int iVar12;
  uint uVar13;
  bool bVar14;
  ushort local_2c;
  
  uVar3 = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
  iVar10 = *(int *)(param_3 + 0x10);
  uVar4 = HcGetBandByWdev(iVar10);
  uVar3 = token_tx_get_queue_by_band(uVar3,uVar4);
  __memzero(param_2,0x2c);
  uVar8 = *(uint *)(param_3 + 0x18);
  if ((uVar8 & 0x100000) != 0) {
    *param_2 = *param_2 | 1;
    uVar8 = *(uint *)(param_3 + 0x18);
  }
  if ((uVar8 & 0x100) != 0) {
    *param_2 = *param_2 | 8;
  }
  iVar5 = RtmpDrvPciMapSingle(param_1,param_3,0,1,0xff00);
  uVar8 = *(uint *)(param_3 + 0x28);
  if (uVar8 < 0x1000) {
    *(int *)(param_2 + 4) = iVar5;
    uVar11 = 1;
    param_2[0x10] = (ushort)((uint)(*(int *)(param_3 + 0x28) << 0x14) >> 0x14);
  }
  else {
    uVar7 = 0;
    uVar13 = uVar8 / 0xfff;
    uVar8 = uVar8 % 0xfff;
    local_2c = (ushort)uVar8;
    if (uVar8 != 0) {
      uVar13 = uVar13 + 1;
    }
    if (uVar8 == 0) {
      local_2c = 0xfff;
    }
    do {
      bVar14 = uVar7 == uVar13 - 1;
      puVar6 = (ushort *)(uVar7 + 2);
      *(int *)(param_2 + (int)puVar6 * 2) = iVar5;
      if (bVar14) {
        puVar6 = param_2 + uVar7;
      }
      if (bVar14) {
        puVar6[0x10] = local_2c;
      }
      else {
        *(undefined1 *)(param_2 + uVar7 + 0x10) = 0xff;
        *(undefined1 *)((int)param_2 + (uVar7 + 0x10) * 2 + 1) = 0xf;
      }
      uVar7 = uVar7 + 1;
      iVar5 = iVar5 + 0xfff;
    } while (uVar7 != uVar13);
    uVar11 = (undefined1)uVar7;
    iVar5 = *(int *)(param_2 + 4);
  }
  iVar12 = *(int *)(param_3 + 0xc);
  if ((*(byte *)(iVar12 + 0x3a) & 8) == 0) {
    uVar2 = token_tx_enq(param_1,uVar3,iVar12,1,*(undefined2 *)(param_3 + 0x1e),iVar5,
                         *(undefined4 *)(iVar12 + 100));
    piVar9 = *(int **)(param_3 + 0x14);
  }
  else {
    *param_2 = *param_2 | 4;
    uVar2 = token_tx_enq(param_1,uVar3,*(int *)(param_3 + 0xc),2,*(undefined2 *)(param_3 + 0x1e),
                         iVar5,*(undefined4 *)(*(int *)(param_3 + 0xc) + 100));
    piVar9 = *(int **)(param_3 + 0x14);
  }
  if ((piVar9 == (int *)0x0) || ((*piVar9 != 0x40001 && ((char)piVar9[0x3a] == '\0')))) {
    iVar5 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0));
    *(byte *)(param_2 + 3) = (byte)((uint)(iVar5 << 0x16) >> 0x1e);
    uVar1 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0));
    *(undefined1 *)((int)param_2 + 5) = uVar1;
  }
  else {
    *(byte *)(param_2 + 3) = (byte)(((uint)*(ushort *)(piVar9 + 0x38) << 0x16) >> 0x1e);
    *(char *)((int)param_2 + 5) = (char)*(undefined2 *)(*(int *)(param_3 + 0x14) + 0xe0);
  }
  uVar1 = *(undefined1 *)(iVar10 + 0x999);
  param_2[1] = uVar2;
  *(undefined1 *)((int)param_2 + 7) = uVar11;
  *(undefined1 *)(param_2 + 2) = uVar1;
  param_3[0x38] = 0x2c;
  uVar2 = *param_2;
  if (uVar2 == 0) {
    param_3[0x21] = *param_3;
    mt_wlan_hook_call(4,param_1,param_3);
    uVar2 = *param_2;
  }
  *param_2 = uVar2 | 0x80;
  if (param_3[0x95] != '\0') {
    *param_2 = uVar2 | 0x180;
  }
  if (param_3[0x97] != '\0') {
    *param_2 = *param_2 | 0x200;
  }
  if (param_3[0x9a] != '\0') {
    *param_2 = *param_2 | 0x400;
  }
  if ((*(short *)(param_3 + 0x9e) != 0) || (param_3[0xa0] != '\0')) {
    *param_2 = *param_2 | 0x800;
  }
  return 0;
}

