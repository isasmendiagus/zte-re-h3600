// module: mt7915.ko
// function: ap_fill_offload_tx_blk @ 0x1aa30
// size: 188 bytes
//

undefined4 ap_fill_offload_tx_blk(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  
  iVar3 = *(int *)(param_3 + 0xc);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar3 + 0x42);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar3 + 0xcc);
  *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar3 + 100);
  if ((*(byte *)(iVar3 + 0x3a) & 8) != 0) {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x100000;
  }
  if (*(char *)(iVar3 + 0x2e) != '\0') {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x100;
  }
  uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar2 & 0x40) != 0) {
    uVar2 = (uint)*(byte *)(param_3 + 5);
    bVar6 = 3 < uVar2;
    bVar4 = uVar2 != 4;
    if (bVar4) {
      bVar6 = uVar2 != 1;
    }
    bVar5 = uVar2 == 2;
    if (!bVar6 || (!bVar4 || bVar5)) {
      uVar2 = *(uint *)(param_3 + 0x18);
    }
    if (!bVar6 || (!bVar4 || bVar5)) {
      uVar2 = uVar2 | 0x800000;
    }
    if (!bVar6 || (!bVar4 || bVar5)) {
      *(uint *)(param_3 + 0x18) = uVar2;
    }
  }
  uVar1 = HcGetWmmIdx(param_1,param_2);
  iVar3 = *(int *)(param_3 + 0x24);
  bVar6 = *(char *)(param_3 + 5) != '\x01';
  *(int *)(param_3 + 0x30) = iVar3;
  if (bVar6) {
    iVar3 = *(int *)(param_3 + 0x14);
  }
  *(undefined1 *)(param_3 + 0x20) = uVar1;
  if (bVar6) {
    *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(iVar3 + 0xf4);
  }
  return 1;
}

