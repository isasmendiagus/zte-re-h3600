// module: mt7915.ko
// function: UAPSD_PacketEnqueue @ 0x1ddf74
// size: 436 bytes
//

/* WARNING: Removing unreachable block (ram,0x001ddfb4) */
/* WARNING: Removing unreachable block (ram,0x001de00c) */

void UAPSD_PacketEnqueue(int param_1,int param_2,undefined4 *param_3,int param_4,char param_5)

{
  int iVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  if (param_2 == 0) {
    RTMPFreeNdisPacket(param_1,param_3);
    if (DebugLevel < 3) {
      return;
    }
    pcVar2 = "uapsd> pEntry == NULL!\n";
    goto LAB_001de0c0;
  }
  iVar1 = param_4 * 0x10;
  iVar5 = param_2 + iVar1;
  if (0xf < *(uint *)(iVar5 + 0xb20)) {
    if (2 < DebugLevel) {
      printk("uapsd> many(%d) WCID(%d) AC(%d)\n",*(uint *)(iVar5 + 0xb20),
             *(undefined2 *)((int)param_3 + 0x42));
    }
    RTMPFreeNdisPacket(param_1,param_3);
    return;
  }
  _raw_spin_lock_bh("BssTableSortByRssi" + param_1 + 0x10);
  if (param_5 == '\0') {
    *param_3 = 0;
    puVar3 = *(undefined4 **)(param_2 + iVar1 + 0xb1c);
    if (puVar3 == (undefined4 *)0x0) {
      *(undefined4 **)(param_2 + iVar1 + 0xb18) = param_3;
    }
    else {
      *puVar3 = param_3;
    }
LAB_001de07c:
    *(undefined4 **)(param_2 + iVar1 + 0xb1c) = param_3;
  }
  else {
    iVar4 = param_2 + iVar1;
    *param_3 = *(undefined4 *)(iVar4 + 0xb18);
    *(undefined4 **)(iVar4 + 0xb18) = param_3;
    if (*(int *)(iVar4 + 0xb1c) == 0) goto LAB_001de07c;
  }
  *(int *)(iVar5 + 0xb20) = *(int *)(iVar5 + 0xb20) + 1;
  _raw_spin_unlock_bh("BssTableSortByRssi" + param_1 + 0x10,0);
  if ((*(byte *)((int)param_3 + 0x3a) & 8) == 0) {
    if (2 < DebugLevel) {
      printk("ps> data (0x%08lx) (AC%d) to uapsd queue (num of pkt = %u)...\n",param_3,param_4,
             *(undefined4 *)(iVar5 + 0xb20));
      return;
    }
  }
  else if (2 < DebugLevel) {
    pcVar2 = "ps> mgmt to uapsd queue...\n";
LAB_001de0c0:
    printk(pcVar2);
    return;
  }
  return;
}

