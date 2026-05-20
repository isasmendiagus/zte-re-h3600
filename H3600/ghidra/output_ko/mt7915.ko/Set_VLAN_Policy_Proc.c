// module: mt7915.ko
// function: Set_VLAN_Policy_Proc @ 0x2c310
// size: 656 bytes
//

undefined4 Set_VLAN_Policy_Proc(int *param_1,char *param_2)

{
  ushort uVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  bool bVar9;
  char *local_2c [2];
  
  iVar7 = *param_1;
  local_2c[0] = param_2;
  iVar2 = hc_get_chip_cap(param_1[0x29e5e8]);
  iVar6 = *(int *)(iVar7 + 0x38);
  iVar7 = *(int *)(iVar7 + 0x3c);
  if ((iVar6 - 0x100U & 0xfffffeff) == 0) {
    iVar6 = iVar7 * 0x160d + 0xadc92;
  }
  else {
    if (iVar6 != 0x400) {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("Unexpected if_type\n");
      return 0;
    }
    iVar6 = iVar7 * 0x84dec + 0xdb6d6;
  }
  pcVar3 = strsep(local_2c,":");
  pcVar4 = strsep(local_2c,":");
  if (pcVar4 == (char *)0x0 || (param_1 + iVar6 == (int *)0x0 || pcVar3 == (char *)0x0)) {
    return 0;
  }
  iVar5 = os_str_tol(pcVar3,0,10);
  uVar1 = os_str_tol(pcVar4,0,10);
  iVar7 = DebugLevel;
  if (4 < uVar1) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Invalid argument\n");
    return 0;
  }
  *(ushort *)((int)(param_1 + iVar6) + ((iVar5 != 0) + 0x47c) * 2 + 6) = uVar1;
  if (0 < iVar7) {
    printk("Set the VLAN checking policy : %d\n",uVar1);
  }
  if ((iVar5 != 0) == 0) {
    return 1;
  }
  if (uVar1 == 3) {
    if (*(char *)(iVar2 + 0x228) == '\0') {
      AsicRxHeaderTransCtl(param_1,1,0,1,0,0);
      goto LAB_0002c444;
    }
  }
  else if (uVar1 == 4) {
    if (*(char *)(iVar2 + 0x228) == '\0') {
      AsicRxHeaderTransCtl(param_1,1,0,1,0,1);
      goto LAB_0002c444;
    }
  }
  else if (uVar1 == 0) {
    AsicRxHeaderTransCtl(param_1,1,0,0,1,0);
    goto LAB_0002c444;
  }
  AsicRxHeaderTransCtl(param_1,1,0,0,0,0);
LAB_0002c444:
  iVar2 = 0;
  puVar8 = (ushort *)(param_1 + 0xaded2);
  while( true ) {
    iVar7 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    bVar9 = SBORROW4(iVar2,0x20);
    iVar6 = iVar2 + -0x20;
    if (iVar2 != 0x20) {
      bVar9 = SBORROW4(iVar2,iVar7);
      iVar6 = iVar2 - iVar7;
    }
    iVar2 = iVar2 + 1;
    if (iVar6 < 0 == bVar9) break;
    *puVar8 = uVar1;
    puVar8 = puVar8 + 0x2c1a;
  }
  *(ushort *)(param_1 + 0xdb916) = uVar1;
  *(ushort *)(param_1 + 0x160702) = uVar1;
  return 1;
}

