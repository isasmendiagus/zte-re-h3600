// module: mt7915.ko
// function: BuildMessageM1 @ 0x1f39f4
// size: 1948 bytes
//

size_t BuildMessageM1(int param_1,int param_2,void *param_3)

{
  undefined1 uVar1;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  void *pvVar7;
  int iVar8;
  bool bVar9;
  int local_44;
  undefined1 local_35;
  undefined2 local_34;
  ushort local_32;
  size_t local_30;
  void *local_2c [2];
  
  iVar8 = *(int *)(param_2 + 0x29ec);
  local_30 = 0;
  local_34 = 0;
  local_32 = 0;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    local_44 = 0;
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    local_44 = 2;
  }
  else {
    local_44 = 0xff;
  }
  puVar6 = (undefined1 *)(param_2 + 0x1bcf);
  puVar5 = (undefined1 *)(param_2 + 0x1bdf);
  local_2c[0] = param_3;
  do {
    uVar1 = RandomByte(param_1);
    puVar6 = puVar6 + 1;
    *puVar6 = uVar1;
  } while (puVar6 != puVar5);
  do {
    uVar1 = RandomByte(param_1);
    puVar5 = puVar5 + 1;
    *puVar5 = uVar1;
  } while (puVar5 != (undefined1 *)(param_2 + 0x1bef));
  iVar2 = AppendWSCTLV(0x104a,local_2c[0],param_2 + 0x70,0);
  puVar6 = (undefined1 *)(param_2 + 0x1b3f);
  puVar5 = (undefined1 *)(param_2 + 0x1b5f);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_35 = 4;
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1022,local_2c[0],&local_35,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1047,local_2c[0],param_2 + 0x2a24,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1020,local_2c[0],param_2 + 0x82,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  do {
    uVar1 = RandomByte(param_1);
    puVar5 = puVar5 + 1;
    *puVar5 = uVar1;
    puVar6 = puVar6 + 1;
    *puVar6 = uVar1;
  } while (puVar5 != (undefined1 *)(param_2 + 0x1b6f));
  *(undefined4 *)(param_2 + 0x1b40) = *(undefined4 *)(param_2 + 0x1b60);
  *(undefined4 *)(param_2 + 0x1b48) = *(undefined4 *)(param_2 + 0x1b68);
  *(undefined4 *)(param_2 + 0x1b4c) = *(undefined4 *)(param_2 + 0x1b6c);
  *(undefined4 *)(param_2 + 0x1b44) = *(undefined4 *)(param_2 + 0x1b64);
  iVar2 = AppendWSCTLV(0x101a,local_2c[0],(undefined4 *)(param_2 + 0x1b60),0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1032,local_2c[0],param_2 + 0x419,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1004,local_2c[0],param_2 + 0xc2,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1010,local_2c[0],param_2 + 0xc4,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x100d,local_2c[0],param_2 + 0xc6,0);
  bVar9 = *(char *)(param_2 + 0x2b31) == '\0';
  uVar4 = (uint)*(ushort *)(param_2 + 10);
  if (bVar9) {
    uVar4 = uVar4 & 0xff;
  }
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  if ((!bVar9) && (local_44 == 0)) {
    uVar4 = uVar4 & 0x210f;
  }
  if (*(char *)(param_2 + 0x70) == '\x10') {
    if (*(int *)(param_2 + 4) == 1) {
      uVar4 = uVar4 | 4;
    }
    else if (*(int *)(param_2 + 4) == 2) {
      uVar4 = uVar4 | 0x8c;
    }
  }
  local_32 = (ushort)((uVar4 & 0xff) << 8) | (ushort)(uVar4 >> 8);
  iVar2 = AppendWSCTLV(0x1008,local_2c[0],&local_32,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  if (local_44 == 0) {
    *(undefined1 *)(param_2 + 0xca) = *(undefined1 *)(param_2 + 8);
  }
  iVar2 = AppendWSCTLV(0x1044,local_2c[0],param_2 + 0xca,0);
  pvVar7 = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  local_2c[0] = pvVar7;
  sVar3 = strlen((char *)(param_2 + 0xcb));
  iVar2 = AppendWSCTLV(0x1021,pvVar7,(char *)(param_2 + 0xcb),sVar3 & 0xffff);
  pvVar7 = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  local_2c[0] = pvVar7;
  sVar3 = strlen((char *)(param_2 + 0x10b));
  iVar2 = AppendWSCTLV(0x1023,pvVar7,(char *)(param_2 + 0x10b),sVar3 & 0xffff);
  pvVar7 = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  local_2c[0] = pvVar7;
  sVar3 = strlen((char *)(param_2 + 299));
  iVar2 = AppendWSCTLV(0x1024,pvVar7,(char *)(param_2 + 299),sVar3 & 0xffff);
  pvVar7 = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  local_2c[0] = pvVar7;
  sVar3 = strlen((char *)(param_2 + 0x14b));
  iVar2 = AppendWSCTLV(0x1042,pvVar7,(char *)(param_2 + 0x14b),sVar3 & 0xffff);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1054,local_2c[0],param_2 + 0xa8,0);
  pvVar7 = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  local_2c[0] = pvVar7;
  sVar3 = strlen((char *)(param_2 + 0x88));
  iVar2 = AppendWSCTLV(0x1011,pvVar7,(char *)(param_2 + 0x88),sVar3 & 0xffff);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x103c,local_2c[0],param_2 + 0x16b,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1002,local_2c[0],param_2 + 0x174,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1012,local_2c[0],param_2 + 0x176,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x1009,local_2c[0],&local_34,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  iVar2 = AppendWSCTLV(0x102d,local_2c[0],param_2 + 0x16c,0);
  local_2c[0] = (void *)((int)local_2c[0] + iVar2);
  local_30 = local_30 + iVar2;
  if (*(char *)(param_2 + 0x2b31) == '\0') {
    if (iVar8 != 0) {
LAB_001f3f88:
      if ((*(char *)(param_1 + 0xa7cbfa) == '\x01') && (*(char *)(iVar8 + 0x3f5d) < '\0')) {
        iVar8 = MAP_InsertMapWscAttr(param_1,iVar8,local_2c[0]);
        local_2c[0] = (void *)((int)local_2c[0] + iVar8);
        local_30 = local_30 + iVar8;
      }
      goto LAB_001f3f9c;
    }
  }
  else {
    WscGenV2Msg(param_2,0,0,0,local_2c,&local_30);
    if ((*(int *)(param_2 + 0x2b28) != 0) && (*(short *)(param_2 + 0x2b26) != 0)) {
      iVar2 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_2c[0]);
      local_2c[0] = (void *)((int)local_2c[0] + iVar2);
      local_30 = local_30 + iVar2;
    }
    if (iVar8 != 0) goto LAB_001f3f88;
LAB_001f3f9c:
    if (((*(char *)(param_2 + 0x2b31) != '\0') && (*(int *)(param_2 + 0x2b28) != 0)) &&
       (*(short *)(param_2 + 0x2b26) != 0)) {
      iVar8 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_2c[0]);
      local_2c[0] = (void *)((int)local_2c[0] + iVar8);
      local_30 = local_30 + iVar8;
    }
  }
  if (DebugLevel < 3) {
    if (*(char *)(param_2 + 0x278d) != '\0') {
      *(undefined1 *)(param_2 + 0x1c53) = 0;
      return local_30;
    }
LAB_001f4034:
    iVar8 = DebugLevel;
    if ((*(char *)(param_2 + 0x1c51) == '\0') || (*(char *)(param_2 + 0x1c52) == '\0')) {
      *(size_t *)(param_2 + 0xadc) = local_30;
      memmove((void *)(param_2 + 0xae0),param_3,local_30);
      *(undefined1 *)(param_2 + 0x1c53) = 0;
      goto joined_r0x001f4058;
    }
  }
  else {
    printk("BuildMessageM1 - bUPnPMsgTimerRunning = %d, pWscControl->WscUseUPnP = %d, pWscControl->EapMsgRunning = %d\n"
           ,*(undefined1 *)(param_2 + 0x278d),*(undefined1 *)(param_2 + 0x1c51),
           *(undefined1 *)(param_2 + 0x1c52));
    if (*(char *)(param_2 + 0x278d) == '\0') goto LAB_001f4034;
  }
  iVar8 = DebugLevel;
  *(undefined1 *)(param_2 + 0x1c53) = 0;
joined_r0x001f4058:
  if (2 < iVar8) {
    printk("BuildMessageM1.\n");
  }
  return local_30;
}

