// module: mt7915.ko
// function: rd_view @ 0x153fec
// size: 580 bytes
//

undefined4 rd_view(int param_1,char *param_2,int param_3)

{
  byte bVar1;
  size_t sVar2;
  size_t sVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  bool bVar12;
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
    printView(param_1,local_1c);
  }
  else {
    sVar2 = strlen(param_2);
    if (sVar2 < 3) {
      sVar3 = strspn(param_2,"0123456789abcdefABCDEF");
      if (sVar2 == sVar3) {
        if (2 < DebugLevel) {
          printk("Vaild strspn=%d,strlen=%d,",sVar2,sVar2);
        }
        bVar1 = os_str_tol(param_2,0,0x10);
        pcVar9 = local_1c;
        *(byte *)(param_1 + 0xa7c2e8) = bVar1;
        sVar2 = strlen(local_1c);
        sprintf(pcVar9 + sVar2,"pRVRDBGCtrl->ucViewLevel = %x",(uint)bVar1);
        goto LAB_00154118;
      }
      if (2 < DebugLevel) {
        printk("Vaild strspn=%d,strlen=%d,",sVar3,sVar2);
      }
    }
    pcVar9 = local_1c;
    sVar2 = strlen(local_1c);
    pcVar10 = local_1c;
    builtin_strncpy(pcVar9 + sVar2,"No corresponding parameter !!!\n",0x20);
    sVar2 = strlen(local_1c);
    pcVar9 = "ex: iwpriv ra0 rd view=FF(bit8)\n";
    pcVar10 = pcVar10 + sVar2;
    do {
      pcVar11 = pcVar10 + 0x10;
      uVar4 = *(undefined4 *)(pcVar9 + 4);
      uVar6 = *(undefined4 *)(pcVar9 + 8);
      uVar7 = *(undefined4 *)(pcVar9 + 0xc);
      bVar12 = pcVar9 != "d view=FF(bit8)\n";
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
      *(undefined4 *)(pcVar10 + 4) = uVar4;
      *(undefined4 *)(pcVar10 + 8) = uVar6;
      *(undefined4 *)(pcVar10 + 0xc) = uVar7;
      pcVar9 = pcVar9 + 0x10;
      pcVar10 = pcVar11;
    } while (bVar12);
    *pcVar11 = '\0';
  }
LAB_00154118:
  pcVar9 = local_1c;
  sVar2 = strlen(local_1c);
  uVar5 = *(uint *)(param_3 + 0x10);
  *(short *)(param_3 + 0x14) = (short)sVar2;
  uVar8 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (!CARRY4(uVar5,sVar2 & 0xffff) && uVar5 + (sVar2 & 0xffff) <= uVar8) {
    uVar8 = 0;
  }
  if (uVar8 == 0) {
    __copy_to_user(uVar5,pcVar9);
    pcVar9 = local_1c;
  }
  os_free_mem(pcVar9);
  if (2 < DebugLevel) {
    printk("%s<-----------------\n","rd_view");
  }
  return 1;
}

