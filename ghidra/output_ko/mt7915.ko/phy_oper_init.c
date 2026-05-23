// module: mt7915.ko
// function: phy_oper_init @ 0x106dbc
// size: 560 bytes
//

void phy_oper_init(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  
  iVar7 = *(int *)(param_1 + 8);
  bVar6 = "SetPartProfileParameters"[iVar7 + 0x18];
  iVar4 = HcGetBandByWdev();
  uVar8 = bVar6 & 0xf;
  bVar6 = bVar6 >> 4;
  if (*(char *)(iVar7 + 0x79504d) != '\0') {
    if (iVar4 == 0) {
      bVar6 = "SetPartProfileParameters"[iVar7 + 0x1a];
      bVar1 = "SetPartProfileParameters"[iVar7 + 0x1b];
    }
    else {
      bVar6 = "rtmp_read_vow_parms_from_file"[iVar7];
      bVar1 = "rtmp_read_vow_parms_from_file"[iVar7 + 1];
    }
    uVar8 = (uint)bVar1;
    if (2 < DebugLevel) {
      printk("%s(): Swap TX/RX Stream number to (%d,%d) since DBDC_MODE EN\n","phy_oper_init",bVar6,
             uVar8);
    }
  }
  *(undefined1 *)(param_2 + 2) = 0;
  uVar3 = wlan_config_get_tx_stream(param_1);
  *(undefined1 *)(param_2 + 5) = uVar3;
  uVar5 = wlan_config_get_rx_stream(param_1);
  iVar2 = DebugLevel;
  *(char *)(param_2 + 6) = (char)uVar5;
  if (2 < iVar2) {
    printk("%s(): obj->tx_stream = %d, obj->rx_stream = %d\n","phy_oper_init",
           *(undefined1 *)(param_2 + 5),uVar5);
    uVar5 = (uint)*(byte *)(param_2 + 6);
  }
  if (bVar6 < *(byte *)(param_2 + 5) || *(byte *)(param_2 + 5) == 0) {
    *(byte *)(param_2 + 5) = bVar6;
  }
  if (uVar5 == 0 || uVar8 < uVar5) {
    *(char *)(param_2 + 6) = (char)uVar8;
  }
  if (((*(uint *)(iVar7 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(iVar7 + 0xa77bb4) != 1 || ((*(uint *)(*(int *)(iVar7 + 0xa77bb8) + 0x4e0) & 1) == 0)
      ))) {
    wlan_config_set_tx_stream(param_1,*(undefined1 *)(param_2 + 5));
    wlan_config_set_rx_stream(param_1,*(undefined1 *)(param_2 + 6));
    bVar6 = *(char *)(param_2 + 5) << 4;
    "SetPartProfileParameters"[iVar7 + 0x18] =
         "SetPartProfileParameters"[iVar7 + 0x18] & 0xfU | bVar6;
    "SetPartProfileParameters"[iVar7 + 0x18] = bVar6 | *(byte *)(param_2 + 6) & 0xf;
    if (*(char *)(iVar7 + 0x79504d) != '\0') {
      if (iVar4 == 0) {
        "SetPartProfileParameters"[iVar7 + 0x1a] = *(char *)(param_2 + 5);
        "SetPartProfileParameters"[iVar7 + 0x1b] = *(char *)(param_2 + 6);
      }
      else {
        "rtmp_read_vow_parms_from_file"[iVar7] = *(char *)(param_2 + 5);
        "rtmp_read_vow_parms_from_file"[iVar7 + 1] = *(char *)(param_2 + 6);
      }
    }
    if (2 < DebugLevel) {
      printk("%s(): normal mode - set to new T/RX\n","phy_oper_init");
    }
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("%s(): operate TxStream = %d, RxStream = %d\n","phy_oper_init",*(undefined1 *)(param_2 + 5)
         ,*(undefined1 *)(param_2 + 6));
  return;
}

