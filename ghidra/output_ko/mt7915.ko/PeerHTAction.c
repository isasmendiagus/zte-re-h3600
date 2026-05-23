// module: mt7915.ko
// function: PeerHTAction @ 0xa1810
// size: 740 bytes
//

void PeerHTAction(int param_1,int param_2)

{
  undefined1 uVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  ushort *puVar9;
  bool bVar10;
  undefined1 auStack_3c [4];
  undefined4 local_38;
  
  puVar9 = (ushort *)(param_2 + 0x920);
  uVar1 = *(undefined1 *)(param_2 + 0x19);
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = *puVar9;
  uVar5 = HcGetMaxStaNum(param_1);
  if (uVar5 <= uVar3) {
    return;
  }
  uVar5 = (uint)*puVar9;
  switch(uVar1) {
  case 0:
    if (3 < DebugLevel) {
      printk("ACTION - HT Notify Channel bandwidth action---->\n");
    }
    if ((*(char *)(param_1 + 0x286285) == '\0') &&
       ((iVar4 = GetStaCfgByWdev(param_1,*(undefined4 *)(uVar5 * 0x14c0 + param_1 + 0xa1d28)),
        iVar4 == 0 || (*(char *)(iVar4 + 0x40e0) == '\0')))) {
      if (2 < DebugLevel) {
        printk("ACTION -Ignore HT Notify Channel BW when link as legacy mode. BW = %d--->\n",
               *(undefined1 *)(param_2 + 0x1a));
      }
    }
    else if (*(char *)(param_2 + 0x1a) == '\0') {
      param_1 = uVar5 * 0x14c0 + param_1;
      *(ushort *)(param_1 + 0xa1ddc) = *(ushort *)(param_1 + 0xa1ddc) & 0xfe7f;
    }
    else {
      iVar4 = uVar5 * 0x14c0 + param_1;
      if (*(int *)(iVar4 + 0xa1d28) == 0) {
        uVar6 = ((uint)*(ushort *)(iVar4 + 0xa1dde) << 0x17) >> 0x1e;
      }
      else {
        uVar3 = *(ushort *)(iVar4 + 0xa1dde);
        uVar6 = wlan_config_get_ht_bw();
        uVar6 = uVar6 & ((uint)uVar3 << 0x17) >> 0x1e;
      }
      param_1 = uVar5 * 0x14c0 + param_1;
      *(ushort *)(param_1 + 0xa1ddc) =
           *(ushort *)(param_1 + 0xa1ddc) & 0xfe7f | (ushort)(uVar6 << 7);
    }
    break;
  case 1:
    if (2 < DebugLevel) {
      printk("ACTION - SMPS action---->\n");
    }
    bVar8 = *(byte *)(param_2 + 0x1a);
    iVar7 = uVar5 * 0x14c0 + param_1;
    bVar10 = (bVar8 & 1) == 0;
    if (bVar10) {
      bVar8 = 3;
    }
    bVar2 = *(byte *)(iVar7 + 0xa2a30);
    if (bVar10) {
      *(byte *)(iVar7 + 0xa2a30) = bVar8;
LAB_000a1950:
      if (bVar8 != bVar2) {
        AsicSetSMPS(param_1,*(undefined2 *)(uVar5 * 0x14c0 + param_1 + 0xa1e00),0);
LAB_000a1978:
        if (*(char *)(iVar4 + 0x150) == '\x01') {
          __memzero(auStack_3c,0x1c);
          local_38 = 5;
          RAParamUpdate(param_1,uVar5 * 0x14c0 + param_1 + 0xa1d20,auStack_3c);
        }
        else if (*(char *)(param_1 + 0x286285) == '\x01') {
          APMlmeDynamicTxRateSwitching(param_1);
        }
      }
    }
    else {
      if ((bVar8 & 2) == 0) {
        *(undefined1 *)(iVar7 + 0xa2a30) = 0;
        bVar8 = 0;
        goto LAB_000a1950;
      }
      *(undefined1 *)(iVar7 + 0xa2a30) = 1;
      if (bVar2 != 1) {
        AsicSetSMPS(param_1,*(undefined2 *)(iVar7 + 0xa1e00));
        goto LAB_000a1978;
      }
    }
    if (2 < DebugLevel) {
      printk("Wcid(%d) MIMO PS = %d, fgRateAdaptFWOffload=%d\n",*puVar9,
             *(undefined1 *)(uVar5 * 0x14c0 + param_1 + 0xa2a30),*(undefined1 *)(iVar4 + 0x150));
    }
    break;
  default:
    if (1 < DebugLevel) {
      printk("%s(): Unknown HT Action:%d\n","PeerHTAction",uVar1);
    }
    break;
  case 3:
  case 4:
    break;
  }
  return;
}

