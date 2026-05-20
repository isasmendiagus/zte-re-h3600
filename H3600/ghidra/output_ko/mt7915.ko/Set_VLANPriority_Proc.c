// module: mt7915.ko
// function: Set_VLANPriority_Proc @ 0x2bfa8
// size: 304 bytes
//

undefined4
Set_VLANPriority_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  iVar5 = *param_1;
  iVar2 = hc_get_chip_cap(param_1[0x29e5e8]);
  uVar1 = os_str_tol(param_2,0,10);
  uVar1 = uVar1 & 0xff;
  if (uVar1 < 8) {
    iVar4 = *(int *)(iVar5 + 0x38);
    iVar5 = *(int *)(iVar5 + 0x3c);
    if ((iVar4 - 0x100U & 0xfffffeff) == 0) {
      iVar5 = iVar5 * 0x160d + 0xadc92;
    }
    else {
      if (iVar4 != 0x400) {
        if (DebugLevel < 3) {
          return 0;
        }
        printk("Unexpected if_type\n");
        return 0;
      }
      iVar5 = iVar5 * 0x84dec + 0xdb6d6;
    }
    piVar6 = param_1 + iVar5;
    if (piVar6 != (int *)0x0) {
      *(ushort *)(piVar6 + 0x23f) = uVar1;
      if (*(char *)(iVar2 + 0x228) == '\0') {
        uVar3 = HcGetBandByWdev(piVar6);
        asic_update_vlan_priority(param_1,uVar3,*(undefined1 *)((int)piVar6 + 0x29),uVar1,param_4);
        return 1;
      }
      return 1;
    }
  }
  else if (-1 < DebugLevel) {
    printk("Invalid PCP value\n");
    return 0;
  }
  return 0;
}

