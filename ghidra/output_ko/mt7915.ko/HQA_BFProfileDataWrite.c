// module: mt7915.ko
// function: HQA_BFProfileDataWrite @ 0x272708
// size: 932 bytes
//

undefined4 HQA_BFProfileDataWrite(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  size_t sVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  char *local_6c;
  uint local_68 [5];
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  iVar1 = DebugLevel;
  os_alloc_mem(param_1,&local_6c,0x200);
  if (local_6c == (char *)0x0) {
    uVar8 = 3;
    goto LAB_00272a14;
  }
  uVar3 = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
  if (uVar3 < 0x49) {
    memcpy(local_68,(void *)(param_3 + 0xc),uVar3);
    uVar3 = uVar3 >> 2;
    if (uVar3 != 0) goto LAB_00272774;
  }
  else {
    if (2 < DebugLevel) {
      printk("%s: command length is wrong\n","HQA_BFProfileDataWrite");
    }
    memcpy(local_68,(void *)(param_3 + 0xc),0x48);
    uVar3 = 0x12;
LAB_00272774:
    uVar6 = 0;
    puVar5 = local_68;
    do {
      uVar6 = uVar6 + 1;
      uVar7 = *puVar5;
      *puVar5 = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
                uVar7 >> 0x18;
      puVar5 = puVar5 + 1;
    } while (uVar6 < uVar3);
  }
  puVar5 = local_68;
  iVar9 = 0;
  DebugLevel = 1;
  while( true ) {
    iVar9 = iVar9 + 1;
    puVar5 = puVar5 + 1;
    if (iVar9 == 0x12) break;
    if (2 < DebugLevel) {
      printk("DWORD%d:%08x\n",iVar9,*puVar5);
    }
  }
  __memzero(local_6c,0x200);
  uVar8 = 0;
  sprintf(local_6c,"%02x:",local_68[0]);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_68[1]);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_68[2]);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_68[3]);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_68[4]);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_54);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_50);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_4c);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_48);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_44);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_40);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_3c);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%03x:",local_38);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_34);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_30);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_2c);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x:",local_28);
  pcVar2 = local_6c;
  sVar4 = strlen(local_6c);
  sprintf(pcVar2 + sVar4,"%02x",local_24);
  Set_TxBfProfileDataWrite(param_1,local_6c);
  os_free_mem(local_6c);
LAB_00272a14:
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_BFProfileDataWrite");
  }
  FUN_0026cdd0(param_3,param_2,2,uVar8);
  DebugLevel = iVar1;
  return uVar8;
}

