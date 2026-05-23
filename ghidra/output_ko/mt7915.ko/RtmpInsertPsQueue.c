// module: mt7915.ko
// function: RtmpInsertPsQueue @ 0x1dd43c
// size: 456 bytes
//

undefined4 RtmpInsertPsQueue(int param_1,undefined4 *param_2,int param_3,uint param_4)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar1 = (uint)(*(int *)(param_3 + 0xb4) << 0x14) >> 0x1f;
  uVar5 = (uint)*(ushort *)(param_3 + 0xe0);
  if (3 < param_4) {
    uVar1 = 0;
  }
  if ((uVar1 == 0) || (*(char *)(param_3 + param_4 + 0xb11) == '\0')) {
    if (0x7f < *(uint *)(param_1 + uVar5 * 0x620 + 0x2f70c)) {
      RTMPFreeNdisPacket(param_1,param_2);
      return 1;
    }
    if (2 < DebugLevel) {
      printk("legacy ps> queue a packet!\n");
    }
    _raw_spin_lock_bh(param_1 + 0x285c50);
    *param_2 = 0;
    iVar3 = param_1 + uVar5 * 0x620;
    iVar4 = param_1 + uVar5 * 0x620;
    puVar2 = *(undefined4 **)(iVar3 + 0x2f708);
    if (puVar2 == (undefined4 *)0x0) {
      *(undefined4 **)(iVar3 + 0x2f704) = param_2;
    }
    else {
      *puVar2 = param_2;
    }
    *(undefined4 **)(iVar4 + 0x2f708) = param_2;
    *(int *)(iVar4 + 0x2f70c) = *(int *)(iVar4 + 0x2f70c) + 1;
    _raw_spin_unlock_bh(param_1 + 0x285c50);
  }
  else {
    UAPSD_PacketEnqueue(param_1,param_3,param_2,param_4,0);
  }
  if ((((*(uint *)(param_3 + 0xb4) & 0x800) != 0) &&
      ((((*(char *)(param_3 + 0xb14) == '\0' || (*(char *)(param_3 + 0xb13) == '\0')) ||
        (*(char *)(param_3 + 0xb12) == '\0')) || (*(char *)(param_3 + 0xb11) == '\0')))) &&
     (*(char *)(param_3 + param_4 + 0xb11) != '\0')) {
    return 0;
  }
  iVar3 = (uint)*(byte *)(param_3 + 0xe4) * 0x5834 + param_1 +
          (((uint)*(ushort *)(param_3 + 0xf8) << 0x15) >> 0x18);
  "vow_watf_q_lv1: %d\n"[iVar3 + 0x13] =
       *(byte *)((int)&NUM_BIT8 + (*(ushort *)(param_3 + 0xf8) & 7)) |
       "vow_watf_q_lv1: %d\n"[iVar3 + 0x13];
  return 0;
}

