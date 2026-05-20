// module: mt7915.ko
// function: mt_rx_pkt_process @ 0xcd400
// size: 1076 bytes
//

undefined4 mt_rx_pkt_process(int param_1,undefined4 param_2,int param_3,void *param_4)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  void *__dest;
  bool bVar4;
  int local_30;
  void *local_2c;
  
  iVar1 = hif_get_resource_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 4) {
    uVar2 = asic_get_packet_type(param_1,*(undefined4 *)((int)param_4 + 0xcc));
    bVar4 = 0xb < uVar2;
    if (uVar2 != 0xc) {
      bVar4 = uVar2 != 2;
    }
    if (bVar4 && (uVar2 != 0xc && uVar2 != 3)) {
      if (0 < DebugLevel) {
        printk("%s(): RXDATATYPE ERROR  PktType:%d (res_attr:%d)\n","mt_rx_pkt_process",uVar2,4);
      }
      RTMPFreeNdisPacket(param_1,param_4);
      wlan_dbg_radio_statistics_inc(0,0x15);
      return 0;
    }
  }
  else {
    uVar2 = asic_get_packet_type(param_1,param_4);
    if (uVar2 - 2 < 2) {
      pvVar3 = (void *)idm_skb_stack_pop(1,0x6a4);
      if (pvVar3 == (void *)0x0) {
        pvVar3 = (void *)__alloc_skbuff(0x6c4,0x20,0,0xffffffff);
        if (pvVar3 == (void *)0x0) {
          hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
          return 0;
        }
        g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
        *(ushort *)((int)pvVar3 + 0xbc) = *(ushort *)((int)pvVar3 + 0xbc) & 0xff0f | 0x40;
        *(int *)((int)pvVar3 + 0xc0) = *(int *)((int)pvVar3 + 0xc0) + 0x20;
        *(int *)((int)pvVar3 + 0xcc) = *(int *)((int)pvVar3 + 0xcc) + 0x20;
      }
      else {
        *(ushort *)((int)pvVar3 + 0xbc) = *(ushort *)((int)pvVar3 + 0xbc) & 0xff0f | 0x40;
        g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
      }
      __dest = (void *)skb_put(pvVar3,0x6a4);
      memcpy(__dest,param_4,0x6a4);
      hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
      param_4 = pvVar3;
    }
  }
  switch(uVar2) {
  case 0:
    local_30 = param_1;
    local_2c = param_4;
    mt_notify_call_chain(param_1 + 0xa18fc,1,&local_30);
switchD_000cd4d4_caseD_0:
    chip_txs_handler(param_1,param_4);
    hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    return 0;
  case 1:
    local_30 = param_1;
    local_2c = param_4;
    mt_notify_call_chain(param_1 + 0xa18fc,2,&local_30);
switchD_000cd4d4_caseD_1:
    asic_rxv_handler(param_1,param_3,param_4);
    hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    return 0;
  default:
    switch(uVar2) {
    case 0:
      goto switchD_000cd4d4_caseD_0;
    case 1:
      goto switchD_000cd4d4_caseD_1;
    case 2:
    case 3:
      wlan_dbg_radio_statistics_inc(0,9);
      if ((*(uint *)(param_1 + 0xa39f84) & 0x40) != 0) {
        RTMPFreeNdisPacket(param_1,param_4);
        wlan_dbg_set_last_error(0,1,0x319,"rx_data_handler");
        return 0;
      }
      iVar1 = asic_trans_rxd_into_rxblk(param_1,param_3,param_4);
      if (iVar1 != 0) {
        iVar1 = header_packet_process(param_1,param_4,param_3);
        if (iVar1 != 0) {
          return 0;
        }
        rx_packet_process(param_1,param_4,param_3);
        return 0;
      }
      RTMPFreeNdisPacket(param_1,param_4);
      wlan_dbg_set_last_error(0,1,799,"rx_data_handler");
      return 0;
    case 4:
      break;
    default:
      if (0 < DebugLevel) {
        printk("%s():Invalid PktType:%d (res_attr:%d)\n","mt_rx_pkt_process",uVar2,iVar1);
      }
      if (iVar1 == 4) {
        RTMPFreeNdisPacket(param_1,param_4);
        return 0;
      }
      break;
    case 6:
      goto switchD_000cd4d4_caseD_6;
    case 7:
      goto switchD_000cd4d4_caseD_7;
    case 0xc:
      dbg_log_wrapper(param_1,0xc,param_4,0);
      RTMPFreeNdisPacket(param_1,param_4);
      return 0;
    }
    break;
  case 4:
    local_30 = param_1;
    local_2c = param_4;
    mt_notify_call_chain(param_1 + 0xa18fc,4,&local_30);
    break;
  case 6:
    local_30 = param_1;
    local_2c = param_4;
    mt_notify_call_chain(param_1 + 0xa18fc,5,&local_30);
switchD_000cd4d4_caseD_6:
    asic_txdone_handle(param_1,param_4,param_2);
    hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    return 0;
  case 7:
    local_30 = param_1;
    local_2c = param_4;
    mt_notify_call_chain(param_1 + 0xa18fc,3,&local_30);
switchD_000cd4d4_caseD_7:
    asic_rx_event_handler(param_1,param_4);
    *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x10000;
    hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    return 0;
  }
  hif_free_rx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_2);
  return 0;
}

