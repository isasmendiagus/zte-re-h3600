// module: mt7915.ko
// function: rx_packet_process @ 0xcd1f8
// size: 508 bytes
//

undefined4 rx_packet_process(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  void *__s2;
  int iVar4;
  
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(param_1 + 0xa77bb4) != 1 ||
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
    if (*(byte **)(param_3 + 0x1c) == (byte *)0x0) {
      RTMPFreeNdisPacket(param_1,param_2);
      wlan_dbg_set_last_error(0,1,0x1c63,"rx_packet_process");
    }
    else {
      uVar3 = ((uint)**(byte **)(param_3 + 0x1c) << 0x1c) >> 0x1e;
      if (uVar3 == 1) {
        wlan_dbg_radio_statistics_inc(0,0xc);
        dev_rx_ctrl_frm(param_1,param_3);
        return 0;
      }
      if (uVar3 == 2) {
        wlan_dbg_radio_statistics_inc(0,10);
        if ((*(uint *)(param_3 + 0x44) & 0x40000) == 0) {
          dev_rx_802_11_data_frm(param_1,param_3);
        }
        else {
          remove_vlan_hw_padding();
          iVar4 = *(int *)(param_3 + 0x3c);
          __s2 = (void *)(iVar4 + 0xc);
          iVar1 = memcmp(&TPID,__s2,2);
          if ((iVar1 == 0) && (iVar1 = memcmp(&EAPOL,(void *)(iVar4 + 0x10),2), iVar1 == 0)) {
            remove_vlan_tag(param_1,*(undefined4 *)(param_3 + 0x38));
            uVar2 = *(undefined4 *)(*(int *)(param_3 + 0x38) + 0xcc);
            *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -4;
            *(undefined4 *)(param_3 + 0x3c) = uVar2;
            update_rxblk_addr(param_3);
            rebuild_802_11_eapol_frm(param_1,param_3);
            dev_rx_802_11_data_frm(param_1,param_3);
          }
          else {
            iVar1 = memcmp(&EAPOL,__s2,2);
            if (iVar1 == 0) {
              rebuild_802_11_eapol_frm();
              dev_rx_802_11_data_frm(param_1,param_3);
            }
            else {
              dev_rx_802_3_data_frm(param_1,param_3);
            }
          }
        }
      }
      else {
        if (uVar3 != 0) {
          uVar2 = 0x1ca1;
          goto LAB_000cd2ac;
        }
        wlan_dbg_radio_statistics_inc(0,0xb);
        dev_rx_mgmt_frm(param_1,param_3);
      }
    }
  }
  else if (param_2 != 0) {
    uVar2 = 0x1c32;
LAB_000cd2ac:
    wlan_dbg_set_last_error(0,1,uVar2,"rx_packet_process");
    RTMPFreeNdisPacket(param_1,param_2);
    return 0;
  }
  return 0;
}

