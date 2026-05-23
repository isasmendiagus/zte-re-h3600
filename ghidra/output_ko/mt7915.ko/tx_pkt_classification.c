// module: mt7915.ko
// function: tx_pkt_classification @ 0xc6670
// size: 320 bytes
//

int tx_pkt_classification(int param_1,int param_2,int param_3)

{
  sbyte sVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  sVar1 = *(sbyte *)(param_2 + 0x2a);
  iVar4 = (int)*(char *)(param_2 + 0x36);
  if ((iVar4 == 8) || (iVar4 == 9)) {
    return iVar4;
  }
  uVar5 = (uint)*(ushort *)(param_2 + 0x42);
  if (iVar4 == 1) {
    iVar4 = 1;
  }
  else {
    iVar4 = 2;
  }
  uVar3 = HcGetMaxStaNum();
  if ((uVar5 < uVar3) || (iVar2 = param_1, uVar5 != 0)) {
    iVar2 = uVar5 * 0x14c0 + param_1;
  }
  *(int *)(param_3 + 0x14) = iVar2 + 0xa1d20;
  if ((*(byte *)(param_2 + 0x3a) & 8) != 0) {
    if ((*(byte *)(param_2 + 0x3e) & 1) == 0) {
      iVar4 = 6;
    }
    else {
      iVar4 = 7;
    }
    return iVar4;
  }
  if (('\x01' < *(char *)(param_2 + 0x2b)) &&
     (((int)(uint)*(ushort *)(iVar2 + 0xa29e0) >> sVar1 & 1U) == 0)) {
    return 5;
  }
  uVar5 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar5 & 0x400) == 0) {
    uVar3 = *(uint *)(param_3 + 0x18);
  }
  else {
    uVar5 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar3 = *(uint *)(param_3 + 0x18);
    if ((uVar5 & 0x40) != 0) {
      uVar3 = uVar3 | 0x1000000;
      *(uint *)(param_3 + 0x18) = uVar3;
    }
  }
  if (((uVar3 & 0x1000000) == 0) && (((int)(uint)*(ushort *)(iVar2 + 0xa29e2) >> sVar1 & 1U) != 0))
  {
    if (*(char *)(param_1 + 0x9daa0) == '\x01') {
      *(uint *)(param_3 + 0x18) = uVar3 | 0x10000000;
    }
    else {
      iVar4 = 4;
    }
    return iVar4;
  }
  return iVar4;
}

