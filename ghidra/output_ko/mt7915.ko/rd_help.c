// module: mt7915.ko
// function: rd_help @ 0x153714
// size: 704 bytes
//

undefined4 rd_help(undefined4 param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;
  size_t sVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  bool bVar11;
  undefined1 auStack_20 [4];
  char *local_1c [2];
  
  os_alloc_mem(param_1,local_1c,0x800);
  uVar3 = 0;
  if (local_1c[0] != (char *)0x0) {
    __memzero(local_1c[0],0x800);
    pcVar8 = local_1c[0];
    local_1c[0][0] = '\n';
    local_1c[0][1] = '\0';
    sVar2 = strlen(local_1c[0]);
    pcVar1 = local_1c[0];
    pcVar9 = "iwpriv [Interface] rd [Sub-command]\n";
    pcVar8 = pcVar8 + sVar2;
    do {
      pcVar10 = pcVar8;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar5 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar11 = pcVar9 != "e] rd [Sub-command]\n";
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
      *(undefined4 *)(pcVar10 + 4) = uVar3;
      *(undefined4 *)(pcVar10 + 8) = uVar5;
      *(undefined4 *)(pcVar10 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      pcVar8 = pcVar10 + 0x10;
    } while (bVar11);
    builtin_strncpy(pcVar10 + 0x10,"nd]\n",5);
    sVar2 = strlen(local_1c[0]);
    pcVar8 = local_1c[0];
    builtin_strncpy(pcVar1 + sVar2,"Sub-command List\n",0x12);
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s",&_LC4,"Show view level status\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s","view=","Set view level by hex value(8bits 00~FF)\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s","view+=","Enable view level by string\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s","view-=","Disable view level by string\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s","wcid,sta,ap,apcli","Show mac table\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s","wcid=,sta=,ap=,apcli=","Set WCID\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s","reset","Reset all counter\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar8 + sVar2,"%-25s %s",&_LC18,"Show support command info\n");
    pcVar8 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    uVar4 = *(uint *)(param_3 + 0x10);
    *(short *)(param_3 + 0x14) = (short)sVar2;
    uVar7 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    if (!CARRY4(uVar4,sVar2 & 0xffff) && uVar4 + (sVar2 & 0xffff) <= uVar7) {
      uVar7 = 0;
    }
    if (uVar7 == 0) {
      __copy_to_user(uVar4,pcVar8);
      pcVar8 = local_1c[0];
    }
    os_free_mem(pcVar8);
    if (DebugLevel < 3) {
      uVar3 = 1;
    }
    else {
      printk("%s<-----------------\n","rd_help");
      uVar3 = 1;
    }
  }
  return uVar3;
}

