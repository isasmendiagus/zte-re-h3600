// module: mt7915.ko
// function: RTMPReadChannelPwr @ 0x1452d0
// size: 972 bytes
//

void RTMPReadChannelPwr(int param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  byte *pbVar5;
  char cVar6;
  byte local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  
  iVar4 = 0x52;
  pcVar3 = "get_channel_by_reference" + param_1 + 0xc;
  do {
    chip_eeprom_read16(param_1,iVar4,&local_24);
    chip_eeprom_read16(param_1,iVar4 + 0xe,&local_22);
    cVar1 = (char)iVar4;
    pcVar3[0x14] = cVar1 + -0x50;
    iVar4 = iVar4 + 2;
    *pcVar3 = cVar1 + -0x51;
    if (local_24 < 0x20) {
      pcVar3[2] = local_24;
    }
    else {
      pcVar3[2] = '\x05';
    }
    if (local_23 < 0x20) {
      pcVar3[0x16] = local_23;
    }
    else {
      pcVar3[0x16] = '\x05';
    }
    if (local_22 < 0x20) {
      pcVar3[3] = local_22;
    }
    else {
      pcVar3[3] = '\x05';
    }
    if (local_21 < 0x20) {
      pcVar3[0x17] = local_21;
    }
    else {
      pcVar3[0x17] = '\x05';
    }
    pcVar3 = pcVar3 + 0x28;
  } while (iVar4 != 0x60);
  pcVar3 = "set_radar_dbg_log_config_proc" + param_1 + 0x14;
  cVar1 = '$';
  do {
    cVar6 = cVar1 + '\b';
    *pcVar3 = cVar1;
    pcVar3[2] = '\x05';
    pcVar3[3] = '\x05';
    pcVar3[0x16] = '\x05';
    pcVar3[0x17] = '\x05';
    pcVar3[0x2a] = '\x05';
    pcVar3[0x2b] = '\x05';
    pcVar3[0x14] = cVar1 + '\x02';
    pcVar3[0x28] = cVar1 + '\x04';
    pcVar3 = pcVar3 + 0x3c;
    cVar1 = cVar6;
  } while (cVar6 != 'D');
  iVar4 = 0x78;
  pbVar5 = (byte *)("BuildChannelList" + param_1 + 0xb);
  do {
    chip_eeprom_read16(param_1,iVar4,&local_24);
    iVar2 = iVar4 + 0x2e;
    iVar4 = iVar4 + 2;
    chip_eeprom_read16(param_1,iVar2,&local_22);
    if ((byte)(local_24 + 7) < 0x17) {
      pbVar5[-0x15] = local_24;
    }
    if ((byte)(local_23 + 7) < 0x17) {
      pbVar5[-1] = local_23;
    }
    if ((byte)(local_22 + 7) < 0x17) {
      pbVar5[-0x14] = local_22;
    }
    if ((byte)(local_21 + 7) < 0x17) {
      *pbVar5 = local_21;
    }
    pbVar5 = pbVar5 + 0x28;
  } while (iVar4 != 0x84);
  pcVar3 = "wifi_sys_linkdown" + param_1;
  cVar1 = 'd';
  do {
    cVar6 = cVar1 + '\b';
    *pcVar3 = cVar1;
    pcVar3[2] = '\x05';
    pcVar3[3] = '\x05';
    pcVar3[0x16] = '\x05';
    pcVar3[0x17] = '\x05';
    pcVar3[0x2a] = '\x05';
    pcVar3[0x2b] = '\x05';
    pcVar3[0x14] = cVar1 + '\x02';
    pcVar3[0x28] = cVar1 + '\x04';
    pcVar3 = pcVar3 + 0x3c;
    cVar1 = cVar6;
  } while (cVar6 != -0x74);
  "sync_fsm_peer_response_join_action"[param_1 + 6] = '\x05';
  "sync_fsm_peer_response_join_action"[param_1 + 7] = '\x05';
  "sync_fsm_peer_response_join_action"[param_1 + 4] = -0x74;
  iVar4 = 0x84;
  pbVar5 = (byte *)("wpf_init" + param_1 + 3);
  do {
    chip_eeprom_read16(param_1,iVar4,&local_24);
    iVar2 = iVar4 + 0x2e;
    iVar4 = iVar4 + 2;
    chip_eeprom_read16(param_1,iVar2,&local_22);
    if ((byte)(local_24 + 7) < 0x17) {
      pbVar5[-0x15] = local_24;
    }
    if ((byte)(local_23 + 7) < 0x17) {
      pbVar5[-1] = local_23;
    }
    if ((byte)(local_22 + 7) < 0x17) {
      pbVar5[-0x14] = local_22;
    }
    if ((byte)(local_21 + 7) < 0x17) {
      *pbVar5 = local_21;
    }
    pbVar5 = pbVar5 + 0x28;
  } while (iVar4 != 0x94);
  "sync_fsm_peer_response_join_action"[param_1 + 0x18] = -0x6b;
  "sync_fsm_peer_response_join_action"[param_1 + 0x1a] = '\x05';
  "sync_fsm_peer_response_join_action"[param_1 + 0x1b] = '\x05';
  "sync_fsm_join_timeout_action"[param_1 + 10] = '\x05';
  "sync_fsm_join_timeout_action"[param_1 + 0xb] = '\x05';
  "sync_fsm_join_timeout_action"[param_1 + 0x1e] = '\x05';
  "sync_fsm_join_timeout_action"[param_1 + 0x1f] = '\x05';
  "sync_fsm_msg_invalid_state"[param_1 + 0x12] = '\x05';
  "sync_fsm_msg_invalid_state"[param_1 + 0x13] = '\x05';
  "con_wps_scan_done_handler"[param_1 + 10] = '\x05';
  "con_wps_scan_done_handler"[param_1 + 0xb] = '\x05';
  "sync_fsm_scan_timeout_action"[param_1 + 2] = '\x05';
  "sync_fsm_scan_timeout_action"[param_1 + 3] = '\x05';
  "sync_fsm_scan_timeout_action"[param_1 + 0x16] = '\x05';
  "sync_fsm_scan_timeout_action"[param_1 + 0x17] = '\x05';
  "sync_fsm_peer_response_scan_action"[param_1 + 10] = '\x05';
  "sync_fsm_peer_response_scan_action"[param_1 + 0xb] = '\x05';
  "sync_fsm_peer_response_scan_action"[param_1 + 0x1e] = '\x05';
  "sync_fsm_peer_response_scan_action"[param_1 + 0x1f] = '\x05';
  "sync_fsm_peer_request_idle_action"[param_1 + 0xe] = '\x05';
  "sync_fsm_peer_request_idle_action"[param_1 + 0xf] = '\x05';
  "sync_fsm_peer_request_idle_action"[param_1 + 0x22] = '\x05';
  "sync_fsm_peer_request_idle_action"[param_1 + 0x23] = '\x05';
  "sync_fsm_join_timeout_action"[param_1 + 8] = -0x69;
  "sync_fsm_join_timeout_action"[param_1 + 0x1c] = -0x67;
  "sync_fsm_msg_invalid_state"[param_1 + 0x10] = -99;
  "con_wps_scan_done_handler"[param_1 + 8] = -0x61;
  "sync_fsm_scan_timeout_action"[param_1] = -0x5f;
  "sync_fsm_scan_timeout_action"[param_1 + 0x14] = -0x5b;
  "sync_fsm_peer_response_scan_action"[param_1 + 8] = -0x59;
  "sync_fsm_peer_response_scan_action"[param_1 + 0x1c] = -0x57;
  "sync_fsm_peer_request_idle_action"[param_1 + 0xc] = -0x55;
  "sync_fsm_peer_request_idle_action"[param_1 + 0x20] = -0x53;
  iVar4 = 0x94;
  pbVar5 = (byte *)("sync_fsm_join_timeout_action" + param_1 + 0xb);
  do {
    chip_eeprom_read16(param_1,iVar4,&local_24);
    iVar2 = iVar4 + 0x2e;
    iVar4 = iVar4 + 2;
    chip_eeprom_read16(param_1,iVar2,&local_22);
    if ((byte)(local_24 + 7) < 0x17) {
      pbVar5[-0x15] = local_24;
    }
    if ((byte)(local_23 + 7) < 0x17) {
      pbVar5[-1] = local_23;
    }
    if ((byte)(local_22 + 7) < 0x17) {
      pbVar5[-0x14] = local_22;
    }
    if ((byte)(local_21 + 7) < 0x17) {
      *pbVar5 = local_21;
    }
    pbVar5 = pbVar5 + 0x28;
  } while (iVar4 != 0xa0);
  return;
}

