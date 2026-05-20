// module: mt7915.ko
// function: BuildMessageM2 @ 0x1f4190
// size: 2124 bytes
//

size_t BuildMessageM2(int param_1,int param_2,void *param_3)

{
  undefined1 uVar1;
  int iVar2;
  size_t sVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  void *pvVar6;
  size_t __n;
  uint uVar7;
  undefined1 local_15f;
  ushort local_15e;
  size_t local_15c;
  void *local_158;
  uint local_154;
  undefined1 auStack_14e [32];
  undefined1 auStack_12e [32];
  undefined4 local_10e;
  undefined4 local_10a;
  undefined4 local_106;
  undefined4 local_102;
  undefined4 local_fe;
  undefined2 local_fa;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8 [4];
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined1 auStack_28 [4];
  
  puVar5 = (undefined1 *)(param_2 + 0x1bcf);
  puVar4 = (undefined1 *)(param_2 + 0x1bdf);
  local_15c = 0;
  local_158 = param_3;
  do {
    uVar1 = RandomByte(param_1);
    puVar5 = puVar5 + 1;
    *puVar5 = uVar1;
  } while (puVar5 != puVar4);
  do {
    uVar1 = RandomByte(param_1);
    puVar4 = puVar4 + 1;
    *puVar4 = uVar1;
  } while (puVar4 != (undefined1 *)(param_2 + 0x1bef));
  pvVar6 = (void *)(param_2 + 0x599);
  local_154 = 0xc0;
  __memzero(pvVar6,0xc0);
  DH_SecretKey_Generate
            (param_2 + 0x419,0xc0,WPS_DH_P_VALUE,0xc0,param_2 + 0x358,0xc0,pvVar6,&local_154);
  if (local_154 < 0xc0) {
    iVar2 = 0xc0 - local_154;
    __memzero(local_e8,iVar2);
    uVar7 = local_154;
    memcpy((void *)((int)local_e8 + iVar2),pvVar6,local_154);
    memcpy(pvVar6,local_e8,0xc0);
    local_154 = iVar2 + uVar7;
    if (2 < DebugLevel) {
      printk("%s: Do zero padding!\n","BuildMessageM2");
    }
  }
  RT_SHA256(pvVar6,0xc0,auStack_14e);
  puVar4 = (undefined1 *)(param_2 + 0x1b5f);
  puVar5 = (undefined1 *)(param_2 + 0x1b4f);
  iVar2 = AppendWSCTLV(0x104a,local_158,param_2 + 0x70,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  local_15f = 5;
  iVar2 = AppendWSCTLV(0x1022,local_158,&local_15f,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  do {
    uVar1 = RandomByte(param_1);
    puVar4 = puVar4 + 1;
    *puVar4 = uVar1;
    puVar5 = puVar5 + 1;
    *puVar5 = uVar1;
  } while (puVar4 != (undefined1 *)(param_2 + 0x1b6f));
  iVar2 = AppendWSCTLV(0x101a,local_158,(undefined4 *)(param_2 + 0x1b40),0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1039,local_158,(undefined4 *)(param_2 + 0x1b50),0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1048,local_158,param_2 + 0x72,0);
  local_15c = local_15c + iVar2;
  local_158 = (void *)((int)local_158 + iVar2);
  iVar2 = AppendWSCTLV(0x1032,local_158,param_2 + 0x4d9,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1004,local_158,param_2 + 0xc2,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1010,local_158,param_2 + 0xc4,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x100d,local_158,param_2 + 0xc6,0);
  uVar7 = (uint)*(ushort *)(param_2 + 10);
  if (*(char *)(param_2 + 0x2b31) == '\0') {
    uVar7 = uVar7 & 0xff;
  }
  local_15e = (ushort)((uVar7 & 0xff) << 8) | (ushort)(uVar7 >> 8);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1008,local_158,&local_15e,0);
  pvVar6 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  local_158 = pvVar6;
  sVar3 = strlen((char *)(param_2 + 0xcb));
  iVar2 = AppendWSCTLV(0x1021,pvVar6,(char *)(param_2 + 0xcb),sVar3 & 0xffff);
  pvVar6 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  local_158 = pvVar6;
  sVar3 = strlen((char *)(param_2 + 0x10b));
  iVar2 = AppendWSCTLV(0x1023,pvVar6,(char *)(param_2 + 0x10b),sVar3 & 0xffff);
  pvVar6 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  local_158 = pvVar6;
  sVar3 = strlen((char *)(param_2 + 299));
  iVar2 = AppendWSCTLV(0x1024,pvVar6,(char *)(param_2 + 299),sVar3 & 0xffff);
  pvVar6 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  local_158 = pvVar6;
  sVar3 = strlen((char *)(param_2 + 0x14b));
  iVar2 = AppendWSCTLV(0x1042,pvVar6,(char *)(param_2 + 0x14b),sVar3 & 0xffff);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1054,local_158,param_2 + 0xa8,0);
  pvVar6 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  local_158 = pvVar6;
  sVar3 = strlen((char *)(param_2 + 0x88));
  iVar2 = AppendWSCTLV(0x1011,pvVar6,(char *)(param_2 + 0x88),sVar3 & 0xffff);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x103c,local_158,param_2 + 0x16b,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1002,local_158,param_2 + 0x174,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1009,local_158,param_2 + 0x178,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x1012,local_158,param_2 + 0x176,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  iVar2 = AppendWSCTLV(0x102d,local_158,param_2 + 0x16c,0);
  local_158 = (void *)((int)local_158 + iVar2);
  local_15c = local_15c + iVar2;
  if (((*(char *)(param_2 + 0x2b31) != '\0') &&
      (WscGenV2Msg(param_2,0,0,0,&local_158,&local_15c), *(int *)(param_2 + 0x2b28) != 0)) &&
     (*(short *)(param_2 + 0x2b26) != 0)) {
    iVar2 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_158);
    local_158 = (void *)((int)local_158 + iVar2);
    local_15c = local_15c + iVar2;
  }
  local_10a = *(undefined4 *)(param_2 + 0x1b44);
  local_fe = *(undefined4 *)(param_2 + 0x1f6);
  local_fa = *(undefined2 *)(param_2 + 0x1fa);
  local_106 = *(undefined4 *)(param_2 + 0x1b48);
  local_102 = *(undefined4 *)(param_2 + 0x1b4c);
  local_10e = *(undefined4 *)(param_2 + 0x1b40);
  local_f4 = *(undefined4 *)(param_2 + 0x1b54);
  local_f8 = *(undefined4 *)(param_2 + 0x1b50);
  local_f0 = *(undefined4 *)(param_2 + 7000);
  local_ec = *(undefined4 *)(param_2 + 0x1b5c);
  RT_HMAC_SHA256(auStack_14e,0x20,&local_10e,0x26,auStack_12e,0x20);
  WscDeriveKey(auStack_12e,0x20,_LANCHOR1,0x24,local_e8,0x280);
  sVar3 = local_15c;
  *(undefined4 *)(param_2 + 0x1aed) = local_e8[0];
  *(undefined4 *)(param_2 + 0x1af1) = local_e8[1];
  *(undefined4 *)(param_2 + 0x1af5) = local_e8[2];
  *(undefined4 *)(param_2 + 0x1af9) = local_e8[3];
  *(undefined4 *)(param_2 + 0x1afd) = local_d8;
  *(undefined4 *)(param_2 + 0x1b01) = uStack_d4;
  *(undefined4 *)(param_2 + 0x1b05) = uStack_d0;
  *(undefined4 *)(param_2 + 0x1b09) = uStack_cc;
  *(undefined4 *)(param_2 + 0x1b0d) = local_c8;
  *(undefined4 *)(param_2 + 0x1b11) = uStack_c4;
  *(undefined4 *)(param_2 + 0x1b15) = uStack_c0;
  *(undefined4 *)(param_2 + 0x1b19) = uStack_bc;
  *(undefined4 *)(param_2 + 0x1b1d) = local_b8;
  *(undefined4 *)(param_2 + 0x1b21) = uStack_b4;
  *(undefined4 *)(param_2 + 0x1b25) = uStack_b0;
  *(undefined4 *)(param_2 + 0x1b29) = uStack_ac;
  *(undefined4 *)(param_2 + 0x1b2d) = local_a8;
  *(undefined4 *)(param_2 + 0x1b31) = uStack_a4;
  *(undefined4 *)(param_2 + 0x1b35) = uStack_a0;
  *(undefined4 *)(param_2 + 0x1b39) = uStack_9c;
  __n = *(size_t *)(param_2 + 0x12e0);
  if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
    pvVar6 = memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_2 + 0x12e4),__n);
    memmove((void *)((int)pvVar6 + *(int *)(param_2 + 0x12e0)),param_3,local_15c);
    RT_HMAC_SHA256(param_2 + 0x1aed,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n + sVar3,auStack_12e
                   ,0x20);
  }
  iVar2 = AppendWSCTLV(0x1005,local_158,auStack_12e,0);
  sVar3 = iVar2 + local_15c;
  local_158 = (void *)((int)local_158 + iVar2);
  *(size_t *)(param_2 + 0xadc) = sVar3;
  local_15c = sVar3;
  memmove((void *)(param_2 + 0xae0),param_3,sVar3);
  *(undefined1 *)(param_2 + 0x1c53) = 0;
  if (2 < DebugLevel) {
    printk("BuildMessageM2.\n");
    sVar3 = local_15c;
  }
  return sVar3;
}

