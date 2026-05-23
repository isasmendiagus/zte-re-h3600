// module: mt7915.ko
// function: phy_stat_multi_rssi_rsp_handle @ 0x1528e0
// size: 244 bytes
//

void phy_stat_multi_rssi_rsp_handle(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  uint uVar7;
  
  if (param_3 >> 3 != 0) {
    pbVar5 = (byte *)(param_2 + 3);
    puVar6 = (undefined1 *)(*(int *)(param_1 + 0xc) + 2);
    uVar7 = 0;
    do {
      *(undefined2 *)(puVar6 + -2) = *(undefined2 *)(pbVar5 + -1);
      if (3 < DebugLevel) {
        printk("%s(): WlanIdx: %d\n","phy_stat_multi_rssi_rsp_handle");
      }
      iVar2 = 0;
      puVar3 = puVar6;
      pbVar4 = pbVar5;
      do {
        pbVar4 = pbVar4 + 1;
        iVar1 = (int)(*pbVar4 - 0xdc) / 2;
        if (3 < DebugLevel) {
          printk("%s(): ant: %d, rcpi: %d, rssi: %d\n","phy_stat_multi_rssi_rsp_handle",iVar2,
                 (uint)*pbVar4,iVar1);
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
      uVar7 = uVar7 + 1;
      pbVar5 = pbVar5 + 8;
      puVar6 = puVar6 + 6;
    } while (param_3 >> 3 != uVar7);
  }
  return;
}

