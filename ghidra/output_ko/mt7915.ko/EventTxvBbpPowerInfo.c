// module: mt7915.ko
// function: EventTxvBbpPowerInfo @ 0x1a80ac
// size: 840 bytes
//

undefined4 EventTxvBbpPowerInfo(undefined4 param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  byte *pbVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  bool bVar11;
  int local_30;
  int local_2c [2];
  
  local_30 = 0;
  local_2c[0] = 0;
  if (param_3 != 0x28) {
    return 1;
  }
  uVar8 = (uint)*(byte *)(param_2 + 0x24);
  os_alloc_mem(param_1,&local_30,uVar8);
  if (local_30 == 0) {
    return 1;
  }
  os_alloc_mem(param_1,local_2c,uVar8);
  if (local_2c[0] == 0) {
    os_free_mem(local_30);
    return 1;
  }
  os_zero_mem(local_30,uVar8);
  os_zero_mem(local_2c[0],uVar8);
  uVar9 = (uint)*(byte *)(param_2 + 2);
  bVar11 = (*(byte *)(param_2 + 2) & 0x80) != 0;
  if (bVar11) {
    uVar9 = -uVar9;
  }
  if (uVar8 != 0) {
    pbVar4 = (byte *)(param_2 + 3);
    uVar5 = 0;
    do {
      pbVar4 = pbVar4 + 1;
      bVar1 = *pbVar4;
      if ((bVar1 & 0x80) == 0) {
        *(byte *)(local_30 + uVar5) = bVar1;
      }
      else {
        *(byte *)(local_30 + uVar5) = -bVar1;
        *(undefined1 *)(local_2c[0] + uVar5) = 1;
      }
      uVar5 = uVar5 + 1;
    } while ((uVar5 & 0xff) < uVar8);
  }
  cVar2 = *(char *)(param_2 + 1);
  if (DebugLevel < 1) {
    if ((*(byte *)(param_2 + 2) & 1) != 0) goto LAB_001a81b0;
LAB_001a81a8:
    if (DebugLevel < 1) goto LAB_001a81b0;
    puVar7 = &_LC113;
    if (!bVar11) {
      puVar7 = &_LC114;
    }
    pcVar3 = "BAND0";
    if (cVar2 == '\x01') {
      pcVar3 = "BAND1";
    }
    printk("[%s]  TXV Power  (0x%x [%02d:%02d]): 0x%02x     (%s%02d dBm)\n",pcVar3,
           *(undefined4 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x21),
           *(undefined1 *)(param_2 + 0x20),(int)*(char *)(param_2 + 3),puVar7,(uVar9 & 0xff) >> 1);
LAB_001a834c:
    if (DebugLevel < 1) goto LAB_001a81b0;
    printk("-----------------------------------------------------------------------------\n");
    iVar6 = DebugLevel;
    if (uVar8 != 0) goto LAB_001a81b8;
  }
  else {
    printk("=============================================================================\n");
    if ((0 < DebugLevel) &&
       (printk("   Target TXV and BBP POWER INFO (per packet)          \n"), 0 < DebugLevel)) {
      printk("=============================================================================\n");
      if ((*(byte *)(param_2 + 2) & 1) == 0) goto LAB_001a81a8;
      if (0 < DebugLevel) {
        puVar7 = &_LC113;
        if (!bVar11) {
          puVar7 = &_LC114;
        }
        pcVar3 = "BAND0";
        if (cVar2 == '\x01') {
          pcVar3 = "BAND1";
        }
        printk("[%s]  TXV Power  (0x%x [%02d:%02d]): 0x%02x     (%s%02d.5 dBm)\n",pcVar3,
               *(undefined4 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x21),
               *(undefined1 *)(param_2 + 0x20),(int)*(char *)(param_2 + 3),puVar7,
               (uVar9 & 0xff) >> 1);
        goto LAB_001a834c;
      }
    }
LAB_001a81b0:
    if (uVar8 == 0) goto LAB_001a8204;
LAB_001a81b8:
    puVar10 = (undefined4 *)(param_2 + 0xc);
    uVar9 = 0;
    iVar6 = DebugLevel;
    pbVar4 = (byte *)(param_2 + 3);
    do {
      if ((pbVar4[1] & 1) == 0) {
        if (0 < iVar6) {
          bVar1 = pbVar4[5];
          pcVar3 = "[WF%01d]  BBP Power  (0x%x [%02d:%02d]): 0x%02x     (%s%02d dBm)\n";
          goto LAB_001a8238;
        }
      }
      else if (0 < iVar6) {
        bVar1 = pbVar4[5];
        pcVar3 = "[WF%01d]  BBP Power  (0x%x [%02d:%02d]): 0x%02x     (%s%02d.5 dBm)\n";
LAB_001a8238:
        puVar7 = &_LC113;
        if (*(char *)(local_2c[0] + uVar9) != '\x01') {
          puVar7 = &_LC114;
        }
        printk(pcVar3,uVar9,*puVar10,*(undefined1 *)(param_2 + 0x23),*(undefined1 *)(param_2 + 0x22)
               ,(int)(char)bVar1,puVar7,*(byte *)(local_30 + uVar9) >> 1);
        iVar6 = DebugLevel;
      }
      uVar9 = uVar9 + 1;
      puVar10 = puVar10 + 1;
      pbVar4 = pbVar4 + 1;
    } while ((uVar9 & 0xff) < uVar8);
  }
  if (0 < iVar6) {
    printk("-----------------------------------------------------------------------------\n");
  }
LAB_001a8204:
  os_free_mem(local_30);
  os_free_mem(local_2c[0]);
  return 0;
}

