// module: mt7915.ko
// function: mt_ate_tx_v2 @ 0x27ccec
// size: 476 bytes
//

undefined4 mt_ate_tx_v2(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 uVar7;
  uint uVar8;
  int *piVar9;
  undefined4 *puVar10;
  uint uVar11;
  bool bVar12;
  
  iVar3 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  puVar10 = *(undefined4 **)(param_1 + 0xa39fd0);
  iVar4 = net_ad_wrap_service(param_1);
  iVar5 = HcGetBandByWdev(param_2);
  iVar4 = iVar5 * 0xd18 + iVar4;
  cVar1 = *(char *)(iVar4 + 0x1106);
  if (*(char *)(iVar4 + 0x1104) == '\0') {
    uVar7 = 0x18;
    *(undefined1 *)(param_3 + 0x2c) = 0x18;
  }
  else {
    *(char *)(param_3 + 0x2c) = (char)*(undefined4 *)(iVar4 + 0x10fc);
    uVar7 = (undefined1)*(undefined4 *)(iVar4 + 0x10fc);
  }
  bVar12 = cVar1 == '\0';
  if (bVar12) {
    *(undefined1 *)(param_3 + 0x34) = 0;
  }
  else {
    *(undefined1 *)(param_3 + 0x34) = 2;
  }
  *(undefined1 *)(param_3 + 0x35) = uVar7;
  if (bVar12) {
    uVar8 = *(uint *)(param_3 + 0x18) & 0xfffffffd | 0x80000;
  }
  else {
    uVar8 = *(uint *)(param_3 + 0x18) & 0xfff7ffff | 0x80000002;
  }
  *(uint *)(param_3 + 0x18) = uVar8;
  (*(code *)*puVar10)(param_1,param_2,param_3);
  iVar5 = net_ad_wrap_service(param_1);
  iVar4 = HcGetBandByWdev(param_2);
  *(char *)(param_3 + 1) = (char)*(undefined2 *)(iVar4 * 0xd18 + iVar5 + 0x50e);
  iVar5 = HcGetBandByWdev(param_2);
  sVar2 = *(short *)(*(int *)(param_3 + 0xc) + 0x42);
  iVar4 = net_ad_wrap_service(param_1);
  iVar4 = iVar5 * 0xd18 + iVar4;
  uVar8 = (uint)*(byte *)(iVar4 + 0x6f5);
  if (uVar8 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("(%s)Stack for MAC_TABL_ENRTY is empty!\n","mt_ate_search_mac_tbl_entry");
  }
  else {
    piVar9 = (int *)(iVar4 + 0x758);
    uVar11 = 0;
    do {
      piVar9 = piVar9 + 1;
      iVar5 = *piVar9;
      uVar11 = uVar11 + 1;
      if ((iVar5 != 0) && (*(short *)(iVar5 + 0xe0) == sVar2)) {
        *(int *)(param_3 + 0x14) = iVar5;
        *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(iVar5 + 0xf4);
        if (*(char *)(param_1 + 0xa3b8b5) != '\0') {
          *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x40000000;
        }
                    /* WARNING: Could not recover jumptable at 0x0027ceb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar6 = (**(code **)(iVar3 + 0x168))(param_1,param_3);
        return uVar6;
      }
    } while (uVar11 != uVar8);
  }
  if (-1 < DebugLevel) {
    printk("%s: wcid:%d is in-valid in stack!\n","mt_ate_tx_v2",
           *(undefined2 *)(*(int *)(param_3 + 0xc) + 0x42));
  }
  return 1;
}

