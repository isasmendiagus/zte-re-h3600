// module: mt7915.ko
// function: Set_ResetStatCounter_Proc @ 0xdb49c
// size: 504 bytes
//

undefined4 Set_ResetStatCounter_Proc(int *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined1 auStack_54 [68];
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = HcGetBandByWdev();
    if (1 < uVar2) {
      return 0;
    }
  }
  if (2 < DebugLevel) {
    printk("==>Set_ResetStatCounter_Proc\n");
  }
  NICUpdateRawCountersNew(param_1);
  __memzero(param_1 + uVar2 * 0x42 + 0x28e6fe,0x108);
  __memzero(param_1 + 0x28e6f9,0x14);
  __memzero(param_1 + 0x28e782,0x108);
  param_1[(int)("cmd_txbf_en_dynsnd_pfid_intr" + uVar2 * 0x1c + 0x1a)] = 0;
  param_1[(int)("cmd_txbf_en_dynsnd_pfid_intr" + uVar2 * 0x1c + 0x1b)] = 0;
  MtCmdGetTxStatistic(param_1,1,uVar2,0,auStack_54);
  if ((param_1[0x28eb05] & 1U) == 0) {
    if ((param_1[0x29deed] != 1) || (iVar1 = param_1[0x29deee], (*(uint *)(iVar1 + 0x4e0) & 1) == 0)
       ) goto LAB_000db5b8;
  }
  else {
    iVar1 = param_1[0x29deee];
  }
  iVar3 = net_ad_wrap_service(param_1);
  os_zero_mem((uint)*(byte *)(iVar3 + 0x4cc) * 0x1ac + iVar1 + 0x16c,0x1ac);
  iVar1 = net_ad_wrap_service(param_1);
  iVar3 = net_ad_wrap_service(param_1);
  *(undefined4 *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar1 + 0x111c) = 0;
LAB_000db5b8:
  MT_ATEUpdateRxStatistic(param_1,2,0);
  iVar1 = hc_get_chip_cap(param_1[0x29e5e8]);
  if (*(char *)(iVar1 + 0x96) != '\0') {
    piVar4 = param_1 + 0x28a4d;
    iVar1 = 0;
    while( true ) {
      iVar3 = HcGetMaxStaNum(param_1);
      if (iVar3 <= iVar1) break;
      __memzero(piVar4,0x24);
      piVar4 = piVar4 + 0x530;
      iVar1 = iVar1 + 1;
    }
  }
  return 1;
}

