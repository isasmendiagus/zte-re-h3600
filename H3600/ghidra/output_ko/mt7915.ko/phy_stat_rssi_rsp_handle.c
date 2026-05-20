// module: mt7915.ko
// function: phy_stat_rssi_rsp_handle @ 0x152860
// size: 124 bytes
//

void phy_stat_rssi_rsp_handle(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  byte *pbVar4;
  
  puVar3 = *(undefined1 **)(param_1 + 0xc);
  pbVar4 = (byte *)(param_2 + 3);
  iVar2 = 0;
  do {
    pbVar4 = pbVar4 + 1;
    iVar1 = (int)(*pbVar4 - 0xdc) / 2;
    if (3 < DebugLevel) {
      printk("%s(): ant: %d, rcpi: %d, rssi: %d\n","phy_stat_rssi_rsp_handle",iVar2,(uint)*pbVar4,
             iVar1);
    }
    iVar2 = iVar2 + 1;
    if (iVar1 < 1) {
      *puVar3 = (char)iVar1;
    }
    else {
      *puVar3 = 0x81;
    }
    puVar3 = puVar3 + 1;
  } while (iVar2 != 4);
  return;
}

