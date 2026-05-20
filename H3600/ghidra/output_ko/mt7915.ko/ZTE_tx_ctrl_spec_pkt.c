// module: mt7915.ko
// function: ZTE_tx_ctrl_spec_pkt @ 0x15b9e0
// size: 376 bytes
//

void ZTE_tx_ctrl_spec_pkt(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  
  iVar5 = HcGetBandByWdev(param_2);
  iVar6 = *(int *)(param_3 + 0xc);
  if ((*(char *)(iVar6 + 0x2a) != '\0') || (*(short *)(param_2 + 0x8d4) == 0x101)) {
    *(undefined1 *)(param_3 + 0x95) = 1;
    *(undefined1 *)(param_3 + 0x96) = *(undefined1 *)(iVar6 + 0x2a);
  }
  if ((*(uint *)(param_1 + iVar5 * 0x24 + 0xa7d18c) & 0x20000) == 0) {
    if ((((*(byte *)(iVar6 + 0x4e) & 1) == 0) && ((*(byte *)(iVar6 + 0x30) & 1) == 0)) &&
       ((*(byte *)(iVar6 + 0x4e) & 2) == 0)) {
      return;
    }
    *(undefined1 *)(param_3 + 0x95) = 1;
    *(undefined1 *)(param_3 + 0x97) = 1;
    *(undefined1 *)(param_3 + 0x96) = 6;
    *(undefined1 *)(param_3 + 0x98) = 0x1e;
  }
  param_1 = param_1 + iVar5 * 0x24;
  if (*(char *)(param_1 + 0xa7d174) == '\0') {
    return;
  }
  if ((*(byte *)(iVar6 + 0x4e) & 1) != 0) {
    *(undefined1 *)(param_3 + 0x97) = 1;
    uVar7 = *(undefined4 *)(param_1 + 0xa7d180);
    *(undefined1 *)(param_3 + 0x95) = 1;
    *(undefined1 *)(param_3 + 0x99) = 0;
    *(char *)(param_3 + 0x98) = (char)uVar7;
    uVar7 = *(undefined4 *)(param_1 + 0xa7d184);
    bVar2 = *(byte *)(param_3 + 0x9d);
    *(undefined1 *)(param_3 + 0x9a) = 1;
    *(char *)(param_3 + 0x96) = (char)uVar7;
    bVar3 = (byte)((*(uint *)(param_1 + 0xa7d178) & 0xf) << 4);
    *(byte *)(param_3 + 0x9d) = bVar2 & 0xf | bVar3;
    bVar4 = (byte)((*(uint *)(param_1 + 0xa7d188) & 1) << 3);
    *(byte *)(param_3 + 0x9d) = bVar2 & 7 | bVar3 | bVar4;
    uVar7 = *(undefined4 *)(param_1 + 0xa7d17c);
    *(byte *)(param_3 + 0x9d) = bVar2 & 1 | bVar3 | bVar4;
    *(byte *)(param_3 + 0x9c) = *(byte *)(param_3 + 0x9c) & 0xf0 | (byte)uVar7 & 0xf;
    uVar1 = *(ushort *)(param_3 + 0x9c) & 0xfe7f;
    *(ushort *)(param_3 + 0x9c) = uVar1;
    *(byte *)(param_3 + 0x9c) = (byte)uVar1 & 0x8f;
    return;
  }
  return;
}

