// module: mt7915.ko
// function: ap_tx_pkt_allowed @ 0x19e54
// size: 488 bytes
//

byte ap_tx_pkt_allowed(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  ushort local_22 [3];
  
  pbVar6 = *(byte **)(param_3 + 0xcc);
  if (pbVar6 == (byte *)0x0 || *(uint *)(param_3 + 100) < 0xf) {
    return 0;
  }
  bVar1 = *pbVar6;
  if ((bVar1 & 1) != 0) {
    if (*(char *)(param_3 + 0x2c) == '\0') {
      a4_proxy_delete(param_1,*(undefined1 *)(param_2 + 0xe),pbVar6 + 6);
    }
    if (*(char *)(param_2 + 0x888) != '\x01') {
      return 0;
    }
    uVar8 = (uint)*(ushort *)(param_2 + 0x10);
    goto LAB_00019ef0;
  }
  piVar3 = (int *)MacTableLookup(param_1,pbVar6);
  if (piVar3 == (int *)0x0) {
LAB_00019f98:
    uVar8 = 0xffff;
  }
  else {
    if (piVar3[0x3f] != 2) {
      if (*piVar3 != 0x10) {
        hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        return bVar1 & 1;
      }
      goto LAB_00019f98;
    }
    if (piVar3[2] != param_2) goto LAB_00019f98;
    uVar8 = (uint)*(ushort *)(piVar3 + 0x38);
    if (*piVar3 != 0x10) goto LAB_00019ef0;
  }
  if (*(char *)(param_3 + 0x2c) == '\0') {
    a4_proxy_delete(param_1,*(undefined1 *)(param_2 + 0xe),pbVar6 + 6);
  }
  iVar7 = a4_proxy_lookup(param_1,*(undefined1 *)(param_2 + 0xe),pbVar6,0,0,local_22);
  if (iVar7 != 0) {
    uVar8 = (uint)local_22[0];
  }
LAB_00019ef0:
  uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar8 < 0x120 && uVar8 < uVar4) {
    iVar7 = param_1 + uVar8 * 0x620 + 0x2f6a0;
    if ((iVar7 != 0) && (iVar5 = param_1 + uVar8 * 0x620, *(int *)(iVar5 + 0x2f6a0) != 0)) {
      *(short *)(param_3 + 0x42) = (short)uVar8;
      uVar2 = get_frag_num(param_1,param_2,param_3);
      *(undefined1 *)(param_3 + 0x2b) = uVar2;
      iVar7 = RTMPCheckEtherType(param_1,param_3,iVar7,param_2);
      if ((iVar7 != 0) &&
         ((*(char *)(iVar5 + 0x2f762) != '\x02' ||
          ((((*(uint *)(param_2 + 0x2c) & 0x12cf8) != 0 || (*(char *)(param_2 + 0x5c0) == '\x01'))
           && ((*(byte *)(param_3 + 0x30) & 10) != 0)))))) {
        return 1;
      }
    }
  }
  return 0;
}

