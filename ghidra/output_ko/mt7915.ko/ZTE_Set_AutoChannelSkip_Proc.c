// module: mt7915.ko
// function: ZTE_Set_AutoChannelSkip_Proc @ 0x15eff8
// size: 724 bytes
//

undefined4 ZTE_Set_AutoChannelSkip_Proc(int *param_1,char *param_2)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  char *__s;
  size_t sVar4;
  undefined1 *puVar5;
  byte bVar6;
  byte *pbVar7;
  undefined *puVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  undefined1 uStack_65;
  byte local_64 [64];
  
  iVar9 = *param_1;
  if (param_2 == (char *)0x0) {
    return 0;
  }
  if ((*(int *)(iVar9 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  if (0 < DebugLevel) {
    printk("%s: IfIdx %u, SkipList %s\n","ZTE_Set_AutoChannelSkip_Proc",
           *(undefined4 *)(iVar9 + 0x3c),param_2);
  }
  iVar9 = HcGetBandByWdev(param_1 + *(int *)(iVar9 + 0x3c) * 0x160d + 0xadc92);
  if (iVar9 == 0) {
    bVar6 = *(byte *)((int)param_1 + 0x36b862);
    if (bVar6 == 0) {
      uVar10 = 0;
    }
    else {
      pbVar7 = (byte *)((int)param_1 + 0x36b862);
      uVar10 = 0;
      do {
        pbVar7 = pbVar7 + 1;
        if (0xe < *pbVar7 && uVar10 < 0x3b) {
          local_64[uVar10] = *pbVar7;
          uVar10 = uVar10 + 1 & 0xff;
        }
      } while (pbVar7 != (byte *)((int)param_1 + (int)(&DAT_0036b862 + bVar6)));
    }
  }
  else {
    bVar6 = *(byte *)((int)param_1 + 0x36b862);
    uVar10 = 0;
    if (bVar6 != 0) {
      pbVar7 = (byte *)((int)param_1 + 0x36b862);
      uVar10 = 0;
      do {
        pbVar7 = pbVar7 + 1;
        bVar1 = *pbVar7;
        bVar13 = 0x39 < uVar10;
        bVar12 = uVar10 == 0x3a;
        if (uVar10 < 0x3b) {
          bVar13 = 0xc < bVar1;
          bVar12 = bVar1 == 0xd;
        }
        if (!bVar13 || bVar12) {
          local_64[uVar10] = bVar1;
          uVar10 = uVar10 + 1 & 0xff;
        }
      } while (pbVar7 != (byte *)((int)param_1 + (int)(&DAT_0036b862 + bVar6)));
      cVar2 = *param_2;
      goto joined_r0x0015f1bc;
    }
  }
  cVar2 = *param_2;
joined_r0x0015f1bc:
  if (cVar2 == '\0') {
    *(undefined1 *)((int)param_1 + 0x36b862) = 0;
    iVar9 = 0x3b;
    uVar11 = 0;
  }
  else {
    cVar2 = delimitcnt(param_2,&_LC277);
    bVar6 = cVar2 + 1;
    if (0x3b < bVar6) {
      bVar6 = 0x3b;
    }
    *(byte *)((int)param_1 + 0x36b862) = bVar6;
    __s = (char *)rstrtok(param_2,&_LC277);
    if (__s != (char *)0x0) {
      if (*__s != '\0') {
        puVar5 = (undefined1 *)((int)param_1 + 0x36b863);
        iVar9 = 0;
        do {
          sVar4 = strlen(__s);
          if (3 < sVar4) break;
          if (iVar9 < (int)(uint)*(byte *)((int)param_1 + 0x36b862)) {
            uVar3 = simple_strtol(__s,0,10);
            *puVar5 = uVar3;
          }
          puVar5 = puVar5 + 1;
          __s = (char *)rstrtok(0,&_LC277);
          if (__s == (char *)0x0) goto LAB_0015f27c;
          iVar9 = iVar9 + 1;
        } while (*__s != '\0');
      }
      if (-1 < DebugLevel) {
        sVar4 = strlen(__s);
        printk("lxl:len=%d err\n",sVar4);
      }
      return 0;
    }
LAB_0015f27c:
    uVar11 = (uint)*(byte *)((int)param_1 + 0x36b862);
    iVar9 = 0x3b - uVar11;
  }
  if (iVar9 < (int)uVar10) {
    uVar10 = 0x3b - uVar11 & 0xff;
  }
  if (uVar10 != 0) {
    puVar5 = &uStack_65;
    puVar8 = (undefined *)((int)param_1 + (int)(&DAT_0036b862 + uVar11));
    do {
      puVar5 = puVar5 + 1;
      puVar8 = puVar8 + 1;
      *puVar8 = *puVar5;
    } while (puVar8 != (undefined *)((int)param_1 + (int)(&DAT_0036b862 + uVar11 + uVar10)));
  }
  *(char *)((int)param_1 + 0x36b862) = (char)uVar10 + (char)uVar11;
  return 1;
}

