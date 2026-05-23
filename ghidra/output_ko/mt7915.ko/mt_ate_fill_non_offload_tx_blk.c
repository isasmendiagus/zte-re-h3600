// module: mt7915.ko
// function: mt_ate_fill_non_offload_tx_blk @ 0x27cb30
// size: 148 bytes
//

undefined4 mt_ate_fill_non_offload_tx_blk(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  undefined1 auStack_20 [16];
  
  iVar2 = *(int *)(param_3 + 0xc);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar2 + 0x42);
  RTMP_QueryPacketInfo(iVar2,auStack_20,param_3 + 0x24,param_3 + 0x28);
  uVar1 = *(uint *)(param_3 + 0x18);
  *(uint *)(param_3 + 0x18) = uVar1 | 0x100000;
  if (*(char *)(iVar2 + 0x2e) != '\0') {
    *(uint *)(param_3 + 0x18) = uVar1 | 0x100100;
  }
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x40) != 0) {
    uVar1 = (uint)*(byte *)(param_3 + 5);
    bVar5 = 3 < uVar1;
    bVar3 = uVar1 != 4;
    if (bVar3) {
      bVar5 = uVar1 != 1;
    }
    bVar4 = uVar1 == 2;
    if (!bVar5 || (!bVar3 || bVar4)) {
      uVar1 = *(uint *)(param_3 + 0x18);
    }
    if (!bVar5 || (!bVar3 || bVar4)) {
      uVar1 = uVar1 | 0x800000;
    }
    if (!bVar5 || (!bVar3 || bVar4)) {
      *(uint *)(param_3 + 0x18) = uVar1;
    }
  }
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  return 1;
}

