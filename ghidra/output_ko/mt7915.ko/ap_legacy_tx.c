// module: mt7915.ko
// function: ap_legacy_tx @ 0x1d1e0
// size: 280 bytes
//

undefined4 ap_legacy_tx(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r2;
  code *pcVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_2 + 0x904);
  iVar1 = fill_tx_blk();
  if (iVar1 != 0) {
    if ((*(uint *)(param_3 + 0x18) & 0x800000) == 0) {
      pcVar3 = *(code **)(iVar4 + 0x40);
    }
    else {
      pcVar3 = *(code **)(iVar4 + 0x44);
    }
    (*pcVar3)(param_1,param_2,param_3);
    FUN_0001bb8c(param_1,param_2,param_3);
    ZTE_tx_ctrl_spec_pkt(param_1,param_2,param_3);
    uVar2 = 0x5834;
    if ("Query::OID_802_11_GET_COUNTRY_CODE\n"
        [(uint)*(byte *)(param_2 + 0xc) * 0x5834 + param_1 + 0x20] == '\x01') {
      ZTE_tx_ctrl_per_pkt(param_1,param_2,param_3);
      uVar2 = extraout_r2;
    }
    uVar2 = asic_hw_tx(param_1,param_3,uVar2,param_4);
    return uVar2;
  }
  iVar1 = *(int *)(param_3 + 0x78);
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_3 + 0x74);
    if (iVar1 != 0) {
      *(int *)(iVar1 + 0x213194) = *(int *)(iVar1 + 0x213194) + 1;
    }
  }
  else {
    *(int *)(iVar1 + 0x43fc) = *(int *)(iVar1 + 0x43fc) + 1;
  }
  *(int *)(param_1 + 0x9db94) = *(int *)(param_1 + 0x9db94) + 1;
  wlan_dbg_set_last_error(0,0,0xa34,"ap_legacy_tx");
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
  return 1;
}

