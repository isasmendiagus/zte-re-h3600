// module: mt7915.ko
// function: BackgroundScanTimeoutAction @ 0x22e36c
// size: 584 bytes
//

void BackgroundScanTimeoutAction(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  int iStack_5c;
  int local_58 [11];
  undefined4 local_2c;
  
  bVar1 = *(byte *)(param_2 + 0x924);
  uVar10 = (uint)*(byte *)(param_1 + 0xa7922f);
  uVar8 = (uint)*(byte *)(param_1 + 0xa7979d);
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s(): band idx=%d, channel index=%d, ScanType=%d ==========>\n",
           "BackgroundScanTimeoutAction",bVar1 >> 4,uVar10,bVar1 & 0xf);
  }
  if (param_1 + uVar10 * 0x18 == -0xa78ad4) {
    if (-1 < DebugLevel) {
      printk("%s(): p_bgnd_scan_ch == NULL\n","BackgroundScanTimeoutAction");
    }
  }
  else {
    piVar6 = &iStack_5c;
    uVar5 = 0;
    os_zero_mem(piVar6,0x34);
    iVar7 = 0;
    mt_cmd_get_rdd_ipi_hist(param_1,0xc,&iStack_5c);
    iVar3 = DebugLevel;
    do {
      if (3 < iVar3) {
        printk("ChannelIdx [%d] ipi_idx = %d,\t ipi_hist_cnt=\t0x%x \n",uVar10,uVar5,piVar6[1]);
        iVar3 = DebugLevel;
      }
      uVar4 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      bVar12 = 9 < uVar4;
      bVar11 = uVar4 == 10;
      if (uVar4 < 0xb) {
        bVar12 = uVar4 <= uVar8;
        bVar11 = uVar8 == uVar4;
      }
      piVar6 = piVar6 + 1;
      if (!bVar12 || bVar11) {
        iVar7 = iVar7 + *piVar6;
      }
    } while (uVar5 != 0xc);
    iVar9 = param_1 + uVar10 * 0x18;
    *(int *)(iVar9 + 0xa78adc) = iVar7;
    *(undefined4 *)(iVar9 + 0xa78ae0) = local_2c;
    *(int *)(iVar9 + 0xa78ae4) = iVar7;
    if (2 < iVar3) {
      iVar3 = uVar10 * 0x18 + param_1;
      printk("ChannelIdx [%d], Channel=%d, ipi_th=%d, ipi_hist_cnt=0x%x <===============\n",uVar10,
             *(undefined1 *)(iVar3 + 0xa78ad5),uVar8,*(undefined4 *)(iVar3 + 0xa78adc));
    }
    NextBgndScanChannel(param_1,*(undefined1 *)(param_1 + 0xa7905c));
    if (*(char *)(param_1 + 0xa7905c) == '\0' || (bVar1 & 0xf) == 2) {
      BackgroundScanNextChannel(param_1,bVar1,1);
      return;
    }
    if (*(code **)(iVar2 + 0x280) != (code *)0x0) {
      (**(code **)(iVar2 + 0x280))(param_1,8);
    }
    MlmeEnqueue(param_1,0x2b,0xb,0,0,0);
  }
  return;
}

