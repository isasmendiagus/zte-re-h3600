// module: mt7915.ko
// function: rd_wcid @ 0x1539d4
// size: 676 bytes
//

undefined4 rd_wcid(int param_1,char *param_2,int param_3)

{
  size_t sVar1;
  undefined4 uVar2;
  size_t sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  char *pcVar10;
  char *pcVar11;
  char *pcVar12;
  bool bVar13;
  undefined1 auStack_20 [4];
  char *local_1c;
  
  os_alloc_mem(param_1,&local_1c,0x800);
  if (local_1c == (char *)0x0) {
    return 0;
  }
  __memzero(local_1c,0x800);
  local_1c[0] = '\n';
  local_1c[1] = '\0';
  if (param_2 == (char *)0x0) {
    Show_MacTable_Proc(param_1,0);
  }
  else {
    sVar1 = strlen(param_2);
    if (sVar1 < 4) {
      sVar3 = strspn(param_2,"0123456789");
      if (sVar1 == sVar3) {
        if (2 < DebugLevel) {
          printk("Vaild strspn=%d,strlen=%d,",sVar1,sVar1);
        }
        iVar4 = os_str_tol(param_2,0,10);
        if ((-1 < iVar4) &&
           (iVar5 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
           pcVar12 = local_1c, iVar4 <= iVar5)) {
          *(short *)(param_1 + 0xa7c2ea) = (short)iVar4;
          sVar1 = strlen(local_1c);
          sprintf(pcVar12 + sVar1,"pRVRDBGCtrl->wcid = %d",iVar4);
          goto LAB_00153b0c;
        }
      }
      else if (2 < DebugLevel) {
        printk("Invaild strspn=%d,strlen=%d,",sVar3,sVar1);
      }
    }
    pcVar12 = local_1c;
    sVar1 = strlen(local_1c);
    pcVar10 = local_1c;
    builtin_strncpy(pcVar12 + sVar1,"No corresponding parameter !!!\n",0x20);
    sVar1 = strlen(local_1c);
    uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    sprintf(pcVar10 + sVar1,"ex: iwpriv ra0 rd sta=1~%d\n",uVar2);
    pcVar12 = local_1c;
    sVar1 = strlen(local_1c);
    pcVar10 = "or  iwpriv ra0 rd sta=0 for auto search first sta\n";
    pcVar12 = pcVar12 + sVar1;
    do {
      pcVar11 = pcVar12;
      pcVar12 = pcVar11 + 0x10;
      uVar2 = *(undefined4 *)(pcVar10 + 4);
      uVar7 = *(undefined4 *)(pcVar10 + 8);
      uVar8 = *(undefined4 *)(pcVar10 + 0xc);
      bVar13 = pcVar10 != " search first sta\n";
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      *(undefined4 *)(pcVar11 + 4) = uVar2;
      *(undefined4 *)(pcVar11 + 8) = uVar7;
      *(undefined4 *)(pcVar11 + 0xc) = uVar8;
      pcVar10 = pcVar10 + 0x10;
    } while (bVar13);
    pcVar12[0] = 'a';
    pcVar12[1] = '\n';
    pcVar11[0x12] = '\0';
  }
LAB_00153b0c:
  pcVar12 = local_1c;
  sVar1 = strlen(local_1c);
  uVar6 = *(uint *)(param_3 + 0x10);
  *(short *)(param_3 + 0x14) = (short)sVar1;
  uVar9 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (!CARRY4(uVar6,sVar1 & 0xffff) && uVar6 + (sVar1 & 0xffff) <= uVar9) {
    uVar9 = 0;
  }
  if (uVar9 == 0) {
    __copy_to_user(uVar6,pcVar12);
    pcVar12 = local_1c;
  }
  os_free_mem(pcVar12);
  if (2 < DebugLevel) {
    printk("%s<-----------------\n","rd_wcid");
  }
  return 1;
}

