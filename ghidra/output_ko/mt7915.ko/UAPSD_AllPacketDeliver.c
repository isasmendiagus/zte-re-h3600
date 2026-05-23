// module: mt7915.ko
// function: UAPSD_AllPacketDeliver @ 0x1ddc24
// size: 396 bytes
//

/* WARNING: Removing unreachable block (ram,0x001ddc50) */
/* WARNING: Removing unreachable block (ram,0x001ddd90) */

void UAPSD_AllPacketDeliver(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  byte bVar3;
  int *piVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined1 auStack_29 [5];
  
  _raw_spin_lock_bh("BssTableSortByRssi" + param_1 + 0x10);
  iVar2 = *(int *)(param_2 + 0xb5c);
  iVar5 = param_1 + (uint)*(ushort *)(param_2 + 0xe0) * 0x620 + 0x2f6a0;
  if (iVar2 != 0) {
    bVar3 = *(byte *)(iVar2 + 0x32) & 0x7f;
    if (3 < bVar3) {
      bVar3 = 0;
    }
    iVar2 = ge_enq_req(param_1,iVar2,bVar3,iVar5,0);
    if (iVar2 == 0) {
      RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0xb5c));
    }
    *(undefined4 *)(param_2 + 0xb5c) = 0;
    *(undefined2 *)(param_2 + 0xb60) = 0;
  }
  puVar6 = auStack_29 + 1;
  iVar2 = param_2 + -0x40;
  do {
    puVar6 = puVar6 + -1;
    uVar1 = *puVar6;
    while (piVar4 = *(int **)(param_2 + 0xb48), piVar4 != (int *)0x0) {
      iVar7 = *piVar4;
      *piVar4 = 0;
      *(int *)(param_2 + 0xb48) = iVar7;
      if (iVar7 == 0) {
        *(undefined4 *)(param_2 + 0xb4c) = 0;
      }
      *(int *)(param_2 + 0xb50) = *(int *)(param_2 + 0xb50) + -1;
      iVar7 = ge_enq_req(param_1,piVar4,uVar1,iVar5,0);
      if (iVar7 == 0) {
        RTMPFreeNdisPacket(param_1,piVar4);
      }
    }
    param_2 = param_2 + -0x10;
  } while (param_2 != iVar2);
  _raw_spin_unlock_bh("BssTableSortByRssi" + param_1 + 0x10,0);
  return;
}

