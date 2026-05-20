// module: mt7915.ko
// function: ge_deq_data_pkt @ 0xd31e4
// size: 724 bytes
//

int ge_deq_data_pkt(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  short *psVar8;
  
  ge_deq_req(param_1,param_3,param_4);
  if (*(int *)(param_4 + 0x24) == 1) {
    return 1;
  }
  if (3 < DebugLevel) {
    printk("%s(): deq_info:cur_wcid=%d, cur_qidx=%d, pkt_cnt=%d, pkt_bytes=%d\n","ge_deq_data_pkt",
           *(undefined2 *)(param_4 + 8),*(undefined1 *)(param_4 + 3),*(undefined4 *)(param_4 + 0x18)
           ,*(undefined4 *)(param_4 + 0x14));
  }
  iVar3 = deq_packet_gatter(param_1,param_4,param_2);
  if (iVar3 != 0) {
    return iVar3;
  }
  uVar6 = (uint)*(byte *)(param_4 + 3);
  iVar3 = *(int *)(param_4 + 0x20);
  if (3 < uVar6) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Invalid AC Queue Index\n");
    return 0;
  }
  if (DebugLevel < 4) {
    if (iVar3 == 0) {
      return 0;
    }
  }
  else {
    iVar5 = uVar6 * 0x4018 + param_1;
    printk("%s():Success DeQ(QId=%d) for WCID(%d), PktCnt=%d, TxSWQDeQ/EnQ ID=%d/%d\n",
           "ge_deq_report",uVar6,*(undefined2 *)(param_4 + 8),iVar3,
           *(undefined4 *)(iVar5 + 0x28a350),*(undefined4 *)(iVar5 + 0x28a34c));
    if (iVar3 == 0) goto LAB_000d3428;
  }
  iVar7 = param_1 + uVar6 * 4 + 0x28633c;
  _raw_spin_lock_bh(iVar7);
  iVar5 = param_1 + uVar6 * 0x4018;
  do {
    psVar8 = (short *)(param_1 + (uVar6 * 0x200c + *(int *)(iVar5 + 0x28a350)) * 2 + 0x28634c);
    if (*psVar8 != *(short *)(param_4 + 8)) break;
    *psVar8 = 0;
    uVar4 = *(int *)(iVar5 + 0x28a350) + 1;
    if (0x1fff < uVar4) {
      uVar4 = 0;
    }
    iVar3 = iVar3 + -1;
    *(uint *)(iVar5 + 0x28a350) = uVar4;
  } while (iVar3 != 0);
  iVar3 = tx_flow_check_state(param_1,1,uVar6);
  if (iVar3 != 0) {
    iVar5 = param_1 + uVar6 * 0x4018;
    iVar3 = *(int *)(iVar5 + 0x28a34c);
    iVar5 = *(int *)(iVar5 + 0x28a350);
    if (iVar3 < iVar5) {
      iVar3 = -iVar3;
    }
    else {
      iVar3 = 0x2000 - iVar3;
    }
    if (*(uint *)(param_1 + uVar6 * 0x4018 + 0x28a358) < (uint)(iVar5 + iVar3)) {
      tx_flow_set_state_block(param_1,0,1,0,uVar6);
    }
  }
  _raw_spin_unlock_bh(iVar7);
  iVar3 = param_4 + uVar6 * 2;
  sVar1 = *(short *)(iVar3 + 10);
  if (sVar1 != 0) {
    *(short *)(iVar3 + 10) = sVar1 - (short)*(undefined4 *)(param_4 + 0x20);
  }
  uVar2 = *(ushort *)(param_4 + 4);
  uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar2 < uVar4) && (*(ushort *)(param_4 + 4) < 0x120)) {
    *(int *)(param_4 + 0x18) = *(int *)(param_4 + 0x18) - *(int *)(param_4 + 0x20);
  }
LAB_000d3428:
  if (3 < DebugLevel) {
    param_1 = uVar6 * 0x4018 + param_1;
    printk("After DeqReport, tx_swq D/EQIdx=%d/%d, deq_info.q_max_cnt/pkt_cnt=%d/%d\n",
           *(undefined4 *)(param_1 + 0x28a350),*(undefined4 *)(param_1 + 0x28a34c),
           *(undefined2 *)(param_4 + uVar6 * 2 + 10),*(undefined4 *)(param_4 + 0x18));
  }
  return 0;
}

