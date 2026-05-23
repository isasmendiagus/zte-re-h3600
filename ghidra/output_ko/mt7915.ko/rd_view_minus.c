// module: mt7915.ko
// function: rd_view_minus @ 0x154658
// size: 1048 bytes
//

undefined4 rd_view_minus(int param_1,int param_2,int param_3)

{
  int iVar1;
  size_t sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 uVar8;
  char *pcVar9;
  uint uVar10;
  char *pcVar11;
  undefined1 auStack_20 [4];
  char *local_1c [2];
  
  os_alloc_mem(param_1,local_1c,0x800);
  if (local_1c[0] == (char *)0x0) {
    return 0;
  }
  __memzero(local_1c[0],0x800);
  local_1c[0][0] = '\n';
  local_1c[0][1] = '\0';
  if (param_2 == 0) {
LAB_001548ac:
    pcVar9 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    pcVar11 = local_1c[0];
    builtin_strncpy(pcVar9 + sVar2,"No corresponding parameter !!!\n",0x20);
    sVar2 = strlen(local_1c[0]);
    builtin_strncpy(pcVar11 + sVar2,"ex: iwpriv ra0 rd view-=rate\n",0x1e);
    printView(param_1,local_1c[0]);
  }
  else {
    _LANCHOR1 = &_LANCHOR2;
    iVar1 = FUN_00153d9c(param_2);
    pcVar9 = local_1c[0];
    if (iVar1 == 4) {
      *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0xfb;
      sVar2 = strlen(local_1c[0]);
      pcVar11 = "VIEW_MACCOUNTER Disable";
    }
    else {
      if (iVar1 < 5) {
        if (iVar1 == 1) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0xfe;
          sVar2 = strlen(local_1c[0]);
          builtin_strncpy(pcVar9 + sVar2,"VIEW_BASICINFO Disable",0x17);
          goto LAB_00154738;
        }
        if (iVar1 == 2) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0xfd;
          sVar2 = strlen(local_1c[0]);
          builtin_strncpy(pcVar9 + sVar2,"VIEW_WCID Disable",0x12);
          goto LAB_00154738;
        }
        if (iVar1 != -1) goto LAB_00154738;
        goto LAB_001548ac;
      }
      if (iVar1 == 0x10) {
        *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0xef;
        sVar2 = strlen(local_1c[0]);
        builtin_strncpy(pcVar9 + sVar2,"VIEW_NOISE Disable",0x13);
        goto LAB_00154738;
      }
      if (0x10 < iVar1) {
        if (iVar1 == 0x20) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0xdf;
          sVar2 = strlen(local_1c[0]);
          builtin_strncpy(pcVar9 + sVar2,"VIEW_CNNUMBER Disable",0x16);
        }
        else if (iVar1 == 0x80) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0x7f;
          sVar2 = strlen(local_1c[0]);
          builtin_strncpy(pcVar9 + sVar2,"VIEW_OTHERS Disable",0x14);
        }
        goto LAB_00154738;
      }
      if (iVar1 != 8) goto LAB_00154738;
      *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) & 0xf7;
      sVar2 = strlen(local_1c[0]);
      pcVar11 = "VIEW_PHYCOUNTER Disable";
    }
    uVar4 = *(undefined4 *)(pcVar11 + 4);
    uVar6 = *(undefined4 *)(pcVar11 + 8);
    uVar8 = *(undefined4 *)(pcVar11 + 0xc);
    *(undefined4 *)(pcVar9 + sVar2) = *(undefined4 *)pcVar11;
    *(undefined4 *)(pcVar9 + sVar2 + 4) = uVar4;
    uVar4 = *(undefined4 *)(pcVar11 + 0x10);
    uVar5 = *(undefined4 *)(pcVar11 + 0x14);
    *(undefined4 *)(pcVar9 + sVar2 + 8) = uVar6;
    *(undefined4 *)(pcVar9 + sVar2 + 0xc) = uVar8;
    *(undefined4 *)(pcVar9 + sVar2 + 0x10) = uVar4;
    *(undefined4 *)(pcVar9 + sVar2 + 0x14) = uVar5;
  }
LAB_00154738:
  pcVar9 = local_1c[0];
  sVar2 = strlen(local_1c[0]);
  uVar3 = *(uint *)(param_3 + 0x10);
  uVar10 = sVar2 & 0xffff;
  *(short *)(param_3 + 0x14) = (short)sVar2;
  uVar7 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (!CARRY4(uVar3,uVar10) && uVar3 + uVar10 <= uVar7) {
    uVar7 = 0;
  }
  if (uVar7 == 0) {
    __copy_to_user(uVar3,pcVar9,uVar10);
    pcVar9 = local_1c[0];
  }
  os_free_mem(pcVar9);
  if (2 < DebugLevel) {
    printk("%s<-----------------\n","rd_view_minus");
  }
  return 1;
}

