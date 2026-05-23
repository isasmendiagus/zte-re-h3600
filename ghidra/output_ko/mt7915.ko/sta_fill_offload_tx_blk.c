// module: mt7915.ko
// function: sta_fill_offload_tx_blk @ 0x545bc
// size: 396 bytes
//

undefined4 sta_fill_offload_tx_blk(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  iVar7 = *(int *)(param_3 + 0xc);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar7 + 0x42);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar7 + 0xcc);
  *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar7 + 100);
  if ((*(byte *)(iVar7 + 0x3a) & 8) != 0) {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x100000;
  }
  if (*(char *)(iVar7 + 0x2e) != '\0') {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x100;
  }
  uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar3 & 0x40) != 0) {
    uVar3 = (uint)*(byte *)(param_3 + 5);
    bVar10 = 3 < uVar3;
    bVar8 = uVar3 != 4;
    if (bVar8) {
      bVar10 = uVar3 != 1;
    }
    bVar9 = uVar3 == 2;
    if (!bVar10 || (!bVar8 || bVar9)) {
      uVar3 = *(uint *)(param_3 + 0x18);
    }
    if (!bVar10 || (!bVar8 || bVar9)) {
      uVar3 = uVar3 | 0x800000;
    }
    if (!bVar10 || (!bVar8 || bVar9)) {
      *(uint *)(param_3 + 0x18) = uVar3;
    }
  }
  if ((*(byte *)(param_1 + 0xa77bcf) & 1) != 0) {
    cVar1 = *(char *)(param_3 + 5);
    bVar10 = cVar1 != '\0';
    if (cVar1 != '\x01') {
      bVar10 = cVar1 != '\x06';
    }
    if (bVar10 && (cVar1 != '\x01' && cVar1 != '\a')) {
      iVar4 = memcmp((void *)(param_1 + 0x794b5b),(void *)(*(int *)(iVar7 + 0xcc) + 6),6);
      iVar5 = DebugLevel;
      if ((iVar4 != 0) &&
         (*(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x2000, 3 < iVar5)) {
        printk("%s(): Dongle Packet)\n","sta_fill_offload_tx_blk");
      }
      iVar5 = MATEngineTxHandle(param_1,iVar7,0,**(undefined4 **)(param_3 + 0x14));
      if (iVar5 != 0) {
        RTMPFreeNdisPacket(param_1,iVar7);
        *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar5 + 0xcc);
        uVar6 = *(undefined4 *)(iVar5 + 100);
        *(int *)(param_3 + 0xc) = iVar5;
        *(undefined4 *)(param_3 + 0x28) = uVar6;
      }
      if ((*(uint *)(param_3 + 0x18) & 0x800000) != 0) {
        memmove((void *)(*(int *)(*(int *)(param_3 + 0xc) + 0xcc) + 6),(void *)(param_2 + 0x1b),6);
      }
    }
  }
  uVar2 = HcGetWmmIdx(param_1,param_2);
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x20) = uVar2;
  return 1;
}

