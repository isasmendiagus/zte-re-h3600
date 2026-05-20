// module: mt7915.ko
// function: ap_fp_tx_pkt_allowed @ 0x1a03c
// size: 468 bytes
//

bool ap_fp_tx_pkt_allowed(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  ushort local_1a;
  
  pbVar5 = *(byte **)(param_3 + 0xcc);
  if (pbVar5 == (byte *)0x0 || *(uint *)(param_3 + 100) < 0xf) {
    return false;
  }
  bVar1 = *pbVar5;
  if ((bVar1 & 1) != 0) {
    if (*(char *)(param_3 + 0x2c) == '\0') {
      a4_proxy_delete(param_1,*(undefined1 *)(param_2 + 0xe),pbVar5 + 6);
    }
    if (*(char *)(param_2 + 0x888) != '\x01') {
      return false;
    }
    uVar4 = (uint)*(ushort *)(param_2 + 0x10);
    goto LAB_0001a0d8;
  }
  piVar2 = (int *)MacTableLookup(param_1,pbVar5);
  if (piVar2 == (int *)0x0) {
LAB_0001a17c:
    uVar4 = 0xffff;
  }
  else {
    if (piVar2[0x3f] != 2) {
      if (*piVar2 != 0x10) {
        hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        return (bool)(bVar1 & 1);
      }
      goto LAB_0001a17c;
    }
    if (piVar2[2] != param_2) goto LAB_0001a17c;
    uVar4 = (uint)*(ushort *)(piVar2 + 0x38);
    if (*piVar2 != 0x10) goto LAB_0001a0d8;
  }
  if (*(char *)(param_3 + 0x2c) == '\0') {
    a4_proxy_delete(param_1,*(undefined1 *)(param_2 + 0xe),pbVar5 + 6);
  }
  iVar6 = a4_proxy_lookup(param_1,*(undefined1 *)(param_2 + 0xe),pbVar5,0,0,&local_1a);
  if (iVar6 != 0) {
    uVar4 = (uint)local_1a;
  }
LAB_0001a0d8:
  uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar4 < 0x120 && uVar4 < uVar3) {
    iVar6 = param_1 + uVar4 * 0x620 + 0x2f6a0;
    if ((iVar6 != 0) && (*(int *)(param_1 + uVar4 * 0x620 + 0x2f6a0) != 0)) {
      *(short *)(param_3 + 0x42) = (short)uVar4;
      uVar4 = get_frag_num(param_1,param_2,param_3);
      *(char *)(param_3 + 0x2b) = (char)uVar4;
      if (1 < uVar4) {
        iVar6 = RTMPCheckEtherType(param_1,param_3,iVar6,param_2);
        return iVar6 != 0;
      }
      if (uVar4 != 1) {
        return true;
      }
      RTMPSetFlagsOfEtherType(param_1,param_3,iVar6,param_2);
      return true;
    }
  }
  return false;
}

