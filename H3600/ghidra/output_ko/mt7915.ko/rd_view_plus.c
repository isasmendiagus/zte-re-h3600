// module: mt7915.ko
// function: rd_view_plus @ 0x154234
// size: 1056 bytes
//

undefined4 rd_view_plus(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  size_t sVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 uVar10;
  char *pcVar11;
  uint uVar12;
  char *pcVar13;
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
LAB_001544a0:
    pcVar11 = local_1c[0];
    sVar4 = strlen(local_1c[0]);
    pcVar13 = local_1c[0];
    builtin_strncpy(pcVar11 + sVar4,"No corresponding parameter !!!\n",0x20);
    sVar4 = strlen(local_1c[0]);
    builtin_strncpy(pcVar13 + sVar4,"ex: iwpriv ra0 rd view+=rate\n",0x1e);
    printView(param_1,local_1c[0]);
  }
  else {
    _LANCHOR1 = &_LANCHOR2;
    iVar3 = FUN_00153d9c(param_2);
    pcVar11 = local_1c[0];
    if (iVar3 == 4) {
      *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) | 4;
      sVar4 = strlen(local_1c[0]);
      pcVar13 = "VIEW_MACCOUNTER Enable";
    }
    else {
      if (iVar3 < 5) {
        if (iVar3 == 1) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) | 1;
          sVar4 = strlen(local_1c[0]);
          builtin_strncpy(pcVar11 + sVar4,"VIEW_BASICINFO Enable",0x16);
          goto LAB_00154320;
        }
        if (iVar3 == 2) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) | 2;
          sVar4 = strlen(local_1c[0]);
          builtin_strncpy(pcVar11 + sVar4,"VIEW_WCID Enable",0x11);
          goto LAB_00154320;
        }
        if (iVar3 != -1) goto LAB_00154320;
        goto LAB_001544a0;
      }
      if (iVar3 == 0x10) {
        *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) | 0x10;
        sVar4 = strlen(local_1c[0]);
        builtin_strncpy(pcVar11 + sVar4,"VIEW_NOISE Enable",0x12);
        goto LAB_00154320;
      }
      if (0x10 < iVar3) {
        if (iVar3 == 0x20) {
          *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) | 0x20;
          sVar4 = strlen(local_1c[0]);
          builtin_strncpy(pcVar11 + sVar4,"VIEW_CNNUMBER Enable",0x15);
        }
        else if (iVar3 == 0x80) {
          *(byte *)(param_1 + 0xa7c2e8) =
               ~((byte)~(byte)(((uint)*(byte *)(param_1 + 0xa7c2e8) << 0x19) >> 0x18) >> 1);
          sVar4 = strlen(local_1c[0]);
          builtin_strncpy(pcVar11 + sVar4,"VIEW_OTHERS Enable",0x13);
        }
        goto LAB_00154320;
      }
      if (iVar3 != 8) goto LAB_00154320;
      *(byte *)(param_1 + 0xa7c2e8) = *(byte *)(param_1 + 0xa7c2e8) | 8;
      sVar4 = strlen(local_1c[0]);
      pcVar13 = "VIEW_PHYCOUNTER Enable";
    }
    uVar7 = *(undefined4 *)(pcVar13 + 4);
    uVar8 = *(undefined4 *)(pcVar13 + 8);
    uVar10 = *(undefined4 *)(pcVar13 + 0xc);
    *(undefined4 *)(pcVar11 + sVar4) = *(undefined4 *)pcVar13;
    uVar2 = *(undefined2 *)(pcVar13 + 0x14);
    uVar5 = *(undefined4 *)(pcVar13 + 0x10);
    cVar1 = pcVar13[0x16];
    *(undefined4 *)(pcVar11 + sVar4 + 4) = uVar7;
    *(undefined4 *)(pcVar11 + sVar4 + 8) = uVar8;
    *(undefined4 *)(pcVar11 + sVar4 + 0xc) = uVar10;
    *(undefined4 *)(pcVar11 + sVar4 + 0x10) = uVar5;
    *(undefined2 *)(pcVar11 + sVar4 + 0x14) = uVar2;
    pcVar11[sVar4 + 0x16] = cVar1;
  }
LAB_00154320:
  pcVar11 = local_1c[0];
  sVar4 = strlen(local_1c[0]);
  uVar6 = *(uint *)(param_3 + 0x10);
  uVar12 = sVar4 & 0xffff;
  *(short *)(param_3 + 0x14) = (short)sVar4;
  uVar9 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (!CARRY4(uVar6,uVar12) && uVar6 + uVar12 <= uVar9) {
    uVar9 = 0;
  }
  if (uVar9 == 0) {
    __copy_to_user(uVar6,pcVar11,uVar12);
    pcVar11 = local_1c[0];
  }
  os_free_mem(pcVar11);
  if (2 < DebugLevel) {
    printk("%s<-----------------\n","rd_view_plus");
  }
  return 1;
}

