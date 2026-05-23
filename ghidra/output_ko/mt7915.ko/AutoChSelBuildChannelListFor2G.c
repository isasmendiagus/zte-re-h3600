// module: mt7915.ko
// function: AutoChSelBuildChannelListFor2G @ 0x22ef8
// size: 908 bytes
//

void AutoChSelBuildChannelListFor2G(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 uVar6;
  byte bVar7;
  int iVar8;
  char *pcVar9;
  undefined1 *puVar10;
  int iVar11;
  undefined1 *local_2c [2];
  
  iVar1 = wlan_config_get_ht_bw(param_2);
  uVar2 = HcGetBandByWdev(param_2);
  iVar3 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  iVar4 = HcGetAutoChCtrlbyBandIdx(param_1,uVar2);
  *(undefined1 *)(iVar4 + 0xe) = *(undefined1 *)(iVar3 + 0x49c);
  os_alloc_mem(0,local_2c,0x1e0);
  if (local_2c[0] == (undefined1 *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s-----------------> alloc mem failed\n","AutoChSelBuildChannelListFor2G");
    return;
  }
  os_zero_mem(local_2c[0],0x1e0);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","AutoChSelBuildChannelListFor2G");
  }
  if (*(char *)(iVar4 + 0xe) == '\0') {
    uVar5 = 0;
    iVar3 = DebugLevel;
  }
  else {
    iVar11 = 0;
    iVar8 = 0;
    do {
      puVar10 = (undefined1 *)(iVar3 + iVar11);
      iVar11 = iVar11 + 0x14;
      local_2c[0][iVar8 * 8] = *puVar10;
      iVar8 = iVar8 + 1;
      uVar5 = (uint)*(byte *)(iVar4 + 0xe);
    } while (iVar8 < (int)uVar5);
    iVar3 = DebugLevel;
    if (uVar5 != 0) {
      iVar8 = 0;
      do {
        if (2 < iVar3) {
          printk("%s : Ch = %3d\n","AutoChSelBuildChannelListFor2G",local_2c[0][iVar8 * 8]);
          uVar5 = (uint)*(byte *)(iVar4 + 0xe);
          iVar3 = DebugLevel;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < (int)uVar5);
    }
  }
  if (2 < iVar3) {
    printk("%s<-----------------\n","AutoChSelBuildChannelListFor2G");
    uVar5 = (uint)*(byte *)(iVar4 + 0xe);
  }
  if (uVar5 != 0) {
    iVar3 = 0;
    puVar10 = local_2c[0];
    do {
      uVar6 = 0;
      if ((&DAT_0036b862)[param_1] != '\0') {
        if ((&DAT_0036b863)[param_1] != local_2c[0][iVar3 * 8]) {
          pcVar9 = &DAT_0036b863 + param_1;
          do {
            if (pcVar9 == &DAT_0036b863 + param_1 + (uint)(byte)((&DAT_0036b862)[param_1] - 1)) {
              uVar6 = 0;
              goto LAB_00023068;
            }
            pcVar9 = pcVar9 + 1;
          } while (*pcVar9 != local_2c[0][iVar3 * 8]);
        }
        uVar6 = 1;
      }
LAB_00023068:
      puVar10[7] = uVar6;
      iVar3 = iVar3 + 1;
      bVar7 = *(byte *)(iVar4 + 0xe);
      puVar10 = puVar10 + 8;
    } while (iVar3 < (int)(uint)bVar7);
    if (bVar7 == 0) goto LAB_00023194;
    iVar3 = 0;
    do {
      iVar8 = iVar3 * 8;
      local_2c[0][iVar8 + 3] = 0;
      local_2c[0][iVar8 + 2] = local_2c[0][iVar3 * 8];
      if (iVar1 == 0) {
        local_2c[0][iVar8 + 6] = 1;
      }
      else if ((iVar1 == 1) &&
              (iVar11 = N_ChannelGroupCheck(param_1,local_2c[0][iVar8],param_2), iVar11 != 0)) {
        local_2c[0][iVar8 + 6] = 1;
      }
      if ((2 < DebugLevel) &&
         (printk("[AutoChSelBuildChannelListFor2G] - ChIdx = %d,  ChListNum = %d\n",iVar3,
                 *(undefined1 *)(iVar4 + 0xe)), 2 < DebugLevel)) {
        printk("%s:\tPrimChannel =  %3d, CenChannel = %3d, BW= %d, BwCap= %d, SkipChannel= %d\n",
               "AutoChSelBuildChannelListFor2G",local_2c[0][iVar8],local_2c[0][iVar8 + 2],
               local_2c[0][iVar8 + 3],local_2c[0][iVar8 + 6],local_2c[0][iVar8 + 7]);
      }
      uVar5 = (uint)*(byte *)(iVar4 + 0xe);
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)uVar5);
    if (uVar5 != 0) {
      iVar1 = 0;
      puVar10 = local_2c[0];
      do {
        iVar3 = iVar4 + iVar1 * 8;
        if (puVar10[6] != '\0') {
          iVar1 = iVar1 + 1;
          *(undefined1 *)(iVar3 + 0x74) = *puVar10;
          *(undefined1 *)(iVar3 + 0x77) = puVar10[3];
          *(undefined1 *)(iVar3 + 0x7a) = puVar10[6];
          *(undefined1 *)(iVar3 + 0x76) = puVar10[2];
          *(undefined1 *)(iVar3 + 0x7b) = puVar10[7];
          *(undefined1 *)(iVar3 + 0x75) = puVar10[1];
        }
        puVar10 = puVar10 + 8;
      } while (puVar10 != local_2c[0] + uVar5 * 8);
      bVar7 = (byte)iVar1;
      goto LAB_00023194;
    }
  }
  bVar7 = 0;
LAB_00023194:
  *(byte *)(iVar4 + 0xe) = bVar7;
  os_free_mem(local_2c[0]);
  return;
}

