// module: mt7915.ko
// function: indicate_eapol_pkt @ 0xca8c4
// size: 296 bytes
//

void indicate_eapol_pkt(int param_1,int param_2,undefined4 param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_1 == 0) {
    if (1 < DebugLevel) {
      printk("indicate_eapol_pkt: invalid pAd.\n");
    }
    wlan_dbg_set_last_error(0,1,0x12b8,"indicate_eapol_pkt");
    RTMPFreeNdisPacket(0,*(undefined4 *)(param_2 + 0x38));
    return;
  }
  uVar1 = *(ushort *)(param_2 + 0x4e);
  uVar2 = HcGetMaxStaNum();
  if (uVar1 < uVar2) {
    iVar3 = FUN_000c53fc(param_1,param_2);
    if (iVar3 != 0) {
      rx_eapol_frm_handle(param_1,(uint)*(ushort *)(param_2 + 0x4e) * 0x14c0 + param_1 + 0xa1d20,
                          param_2,param_3);
      return;
    }
    if (1 < DebugLevel) {
      printk("%s:drop packet by PN mismatch!\n","indicate_eapol_pkt");
    }
    uVar4 = 0x12c6;
  }
  else {
    if (1 < DebugLevel) {
      printk("indicate_eapol_pkt: invalid wcid.\n");
    }
    uVar4 = 0x12bf;
  }
  wlan_dbg_set_last_error(0,1,uVar4,"indicate_eapol_pkt");
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
  return;
}

