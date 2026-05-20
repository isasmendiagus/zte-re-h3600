// module: mt7915.ko
// function: Set_Scan_SkipList_Proc @ 0x2dbb8
// size: 496 bytes
//

undefined4 Set_Scan_SkipList_Proc(int *param_1,char *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  size_t sVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  bool bVar12;
  char *local_2c [2];
  char *local_24 [2];
  
  iVar11 = *param_1;
  local_24[0] = (char *)0x0;
  if (*(int *)(iVar11 + 0x38) != 0x400 && (*(int *)(iVar11 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  if (param_2 == (char *)0x0) {
    return 0;
  }
  if (*param_2 == '\0') {
    return 0;
  }
  local_2c[0] = param_2;
  sVar3 = strlen(param_2);
  os_alloc_mem(0,local_24,sVar3 + 1);
  pcVar5 = local_24[0];
  if (local_24[0] == (char *)0x0) {
    return 0;
  }
  strcpy(local_24[0],local_2c[0]);
  bVar1 = 0;
  do {
    bVar8 = bVar1;
    uVar10 = (uint)bVar8;
    pcVar4 = strsep(local_24,":");
    bVar1 = bVar8 + 1;
  } while (pcVar4 != (char *)0x0);
  os_free_mem(pcVar5);
  if (0 < DebugLevel) {
    printk("Length of the channel skip list : %d\n",uVar10);
  }
  iVar7 = *(int *)(iVar11 + 0x38);
  uVar9 = (uint)*(byte *)(iVar11 + 0x3c);
  if ((iVar7 - 0x100U & 0xfffffeff) == 0) {
    uVar6 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    bVar12 = 0x1e < uVar9;
    if (uVar9 < 0x20) {
      bVar12 = uVar6 <= uVar9;
    }
    if (!bVar12) goto LAB_0002dca8;
    iVar7 = *(int *)(iVar11 + 0x38);
  }
  bVar12 = uVar9 == 1;
  if (uVar9 < 2) {
    bVar12 = iVar7 == 0x400;
  }
  if (!bVar12) {
    return 0;
  }
LAB_0002dca8:
  if (param_1 + uVar9 * 0x160d != (int *)0xffd48db8) {
    iVar11 = get_scan_ctrl_by_wdev(param_1);
    *(byte *)(iVar11 + 0x79) = bVar8;
    if (*(int *)(iVar11 + 0x7c) != 0) {
      os_free_mem();
    }
    os_alloc_mem(0,iVar11 + 0x7c,uVar10);
    if (*(int *)(iVar11 + 0x7c) != 0) {
      if (uVar10 != 0) {
        uVar9 = 0;
        do {
          pcVar5 = strsep(local_2c,":");
          if (pcVar5 != (char *)0x0) {
            iVar7 = *(int *)(iVar11 + 0x7c);
            uVar2 = os_str_tol(pcVar5,0,10);
            *(undefined1 *)(iVar7 + uVar9) = uVar2;
            if (0 < DebugLevel) {
              printk("Channel %d\n",*(undefined1 *)(*(int *)(iVar11 + 0x7c) + uVar9));
            }
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 != uVar10);
      }
      return 1;
    }
  }
  return 0;
}

