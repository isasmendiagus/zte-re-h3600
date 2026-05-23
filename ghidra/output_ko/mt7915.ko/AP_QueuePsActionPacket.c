// module: mt7915.ko
// function: AP_QueuePsActionPacket @ 0xc6494
// size: 472 bytes
//

void AP_QueuePsActionPacket
               (int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
               byte param_6)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = (uint)param_6;
  uVar3 = (uint)*(ushort *)(param_2 + 0xe0);
  if (*(char *)(param_2 + uVar1 + 0xb11) != '\0') {
    if (2 < DebugLevel) {
      printk("ps> mgmt to UAPSD queue %d ... (IsDelts: %d)\n",uVar1,param_4);
    }
    *(byte *)(param_3 + 0x32) = ~((byte)~(byte)((uVar1 << 0x19) >> 0x18) >> 1);
    UAPSD_PacketEnqueue(param_1,param_2,param_3,uVar1,0);
    if (*(char *)(param_2 + 0xb16) == '\0') {
      return;
    }
    goto LAB_000c6508;
  }
  if (DebugLevel < 3) {
    iVar2 = uVar3 * 8;
    if (0x7f < *(uint *)(param_1 + uVar3 * 0x620 + 0x2f70c)) goto LAB_000c6584;
LAB_000c65c8:
    iVar2 = ge_enq_req(param_1,param_3,uVar1,param_1 + (iVar2 - uVar3) * 0xe0 + 0x2f6a0,0);
    if (iVar2 != 0) {
LAB_000c6508:
      iVar2 = (uint)*(byte *)(param_2 + 0xe4) * 0x5834 + param_1 +
              (((uint)*(ushort *)(param_2 + 0xf8) << 0x15) >> 0x18);
      "vow_watf_q_lv1: %d\n"[iVar2 + 0x13] =
           *(byte *)((int)&NUM_BIT8 + (*(ushort *)(param_2 + 0xf8) & 7)) |
           "vow_watf_q_lv1: %d\n"[iVar2 + 0x13];
      return;
    }
  }
  else {
    printk("ps> mgmt to legacy ps queue... (%d)\n",param_4);
    if (*(uint *)(uVar3 * 0x620 + param_1 + 0x2f70c) < 0x80) {
      iVar2 = uVar3 << 3;
      goto LAB_000c65c8;
    }
  }
  if (2 < DebugLevel) {
    iVar2 = param_1 + uVar3 * 0x620;
    printk("%s(%d): WLAN_TX_DROP, pPacket=%p, QueIdx=%d, ps_queue_num=%d, wcid=%d\n",
           "AP_QueuePsActionPacket",0x4df,param_3,uVar1,*(undefined4 *)(iVar2 + 0x2f70c),
           *(undefined2 *)(iVar2 + 0x2f6a8));
  }
LAB_000c6584:
  RTMPFreeNdisPacket(param_1,param_3);
  return;
}

