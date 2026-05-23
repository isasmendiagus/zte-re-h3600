// module: mt7915.ko
// function: Set_Scan_DFS_CH_Utilization_Proc @ 0x2a604
// size: 220 bytes
//

undefined4
Set_Scan_DFS_CH_Utilization_Proc(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r3;
  int iVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  iVar2 = *param_1;
  iVar4 = *(int *)(iVar2 + 0x38);
  uVar1 = iVar4 - 0x100U & 0xfffffeff;
  if (iVar4 != 0x400 && uVar1 != 0) {
    return 0;
  }
  uVar3 = (uint)*(byte *)(iVar2 + 0x3c);
  if (uVar1 == 0) {
    uVar1 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    bVar5 = 0x1e < uVar3;
    if (uVar3 < 0x20) {
      bVar5 = uVar1 <= uVar3;
    }
    if (!bVar5) goto LAB_0002a660;
    iVar4 = *(int *)(iVar2 + 0x38);
  }
  bVar5 = uVar3 == 1;
  if (uVar3 < 2) {
    bVar5 = iVar4 == 0x400;
  }
  if (!bVar5) {
    return 0;
  }
LAB_0002a660:
  if (param_1 + uVar3 * 0x160d == (int *)0xffd48db8) {
    return 0;
  }
  iVar2 = get_scan_ctrl_by_wdev(param_1);
  if (param_2 == 0) {
    *(undefined1 *)(iVar2 + 0x80) = 0;
    return 0;
  }
  iVar4 = os_str_tol(param_2,0,10,extraout_r3,param_4);
  *(bool *)(iVar2 + 0x80) = iVar4 != 0;
  return 1;
}

