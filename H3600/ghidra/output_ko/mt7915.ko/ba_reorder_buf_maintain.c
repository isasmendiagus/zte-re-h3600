// module: mt7915.ko
// function: ba_reorder_buf_maintain @ 0xa86a4
// size: 156 bytes
//

void ba_reorder_buf_maintain(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  ushort *puVar5;
  
  uVar1 = jiffies;
  uVar4 = 0;
  while( true ) {
    uVar2 = HcGetMaxStaNum(param_1);
    if (uVar2 <= (uVar4 & 0xffff)) break;
    iVar3 = (uVar4 & 0xffff) * 0x14c0;
    if (*(int *)(param_1 + iVar3 + 0xa1d20) != 0) {
      puVar5 = (ushort *)(param_1 + iVar3 + 0xa29f2);
      do {
        puVar5 = puVar5 + 1;
        ba_flush_reordering_timeout_mpdus
                  (param_1,param_1 + 0x1c0,param_1 + 0x1c0 + (uint)*puVar5 * 0x60,uVar1);
      } while (puVar5 != (ushort *)(param_1 + iVar3 + 0xa2a02));
    }
    uVar4 = uVar4 + 1;
  }
  return;
}

