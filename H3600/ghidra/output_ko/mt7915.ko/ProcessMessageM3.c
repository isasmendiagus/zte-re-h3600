// module: mt7915.ko
// function: ProcessMessageM3 @ 0x1f8a30
// size: 1100 bytes
//

undefined4 ProcessMessageM3(int param_1,void *param_2,size_t param_3,char *param_4)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  size_t __n;
  uint __n_00;
  undefined4 uVar8;
  uint uVar9;
  uint *__dest;
  uint *__src;
  ushort uStack_53;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  
  local_4c = 0xffffffff;
  local_50 = 0xffffffff;
  __dest = (uint *)(param_4 + 0x1274);
  RTMPZeroMemory(&local_48,0x20);
  *(size_t *)(param_4 + 0x1270) = param_3;
  memmove(__dest,param_2,param_3);
  if ((int)param_3 < 5) {
    bVar1 = true;
    bVar2 = true;
    uVar9 = 0x30;
    bVar3 = true;
    bVar4 = true;
  }
  else {
    bVar2 = true;
    bVar1 = true;
    bVar3 = true;
    uVar9 = 0x30;
    bVar4 = true;
    puVar7 = __dest;
    do {
      while( true ) {
        uVar6 = *puVar7;
        uStack_53 = (ushort)(uVar6 >> 0x10);
        __n_00 = (uStack_53 & 0xff) << 8 | (uint)(uStack_53 >> 8);
        uVar6 = (uVar6 & 0xff) << 8 | uVar6 >> 8 & 0xff;
        if ((int)param_3 < (int)(__n_00 + 4)) {
          if (2 < DebugLevel) {
            printk("unexpected WSC IE Length(%u)\n",__n_00);
          }
          goto LAB_001f8ba0;
        }
        __src = puVar7 + 1;
        if (uVar6 != 0x1015) break;
        uVar9 = uVar9 ^ 0x20;
        memmove(param_4 + 0x1b40,__src,__n_00);
LAB_001f8b0c:
        param_3 = (param_3 - 4) - __n_00;
        puVar7 = (uint *)((int)__src + __n_00);
        if ((int)param_3 < 5) goto LAB_001f8ba0;
      }
      if (0x1015 < uVar6) {
        if (uVar6 == 0x1039) {
          iVar5 = RTMPCompareMemory(param_4 + 0x1ae0,__src,__n_00);
          if ((iVar5 != 0) && (2 < DebugLevel)) {
            printk("Rx M3 Compare Registrar nonce mismatched\n");
          }
          bVar3 = (bool)(bVar3 ^ 1);
        }
        else if (uVar6 == 0x104a) {
          if ((*param_4 != (char)puVar7[1]) && (-1 < DebugLevel)) {
            printk("Rx WPS Message Version mismatched %02x\n");
          }
          bVar4 = (bool)(bVar4 ^ 1);
        }
        else {
          if (uVar6 != 0x1022) goto LAB_001f8b00;
          if (((char)puVar7[1] != '\a') && (-1 < DebugLevel)) {
            printk("Rx WPS Message Type mismatched %02x\n");
          }
          bVar2 = (bool)(bVar2 ^ 1);
        }
        goto LAB_001f8b0c;
      }
      if (uVar6 == 0x1005) {
        bVar1 = (bool)(bVar1 ^ 1);
        memcpy(&local_50,__src,__n_00);
        goto LAB_001f8b0c;
      }
      if (uVar6 != 0x1014) {
LAB_001f8b00:
        if (2 < DebugLevel) {
          printk("ProcessMessageM3 --> Unknown IE 0x%04x\n");
        }
        goto LAB_001f8b0c;
      }
      memmove(param_4 + 0x1b20,__src,__n_00);
      param_3 = (param_3 - 4) - __n_00;
      uVar9 = uVar9 ^ 0x10;
      puVar7 = (uint *)((int)__src + __n_00);
    } while (4 < (int)param_3);
LAB_001f8ba0:
    param_3 = *(size_t *)(param_4 + 0x1270);
  }
  __n = *(size_t *)(param_4 + 0xa6c);
  if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
    memmove(*(void **)(param_1 + 0xa77c3c),param_4 + 0xa70,__n);
    memmove((void *)(*(int *)(param_1 + 0xa77c3c) + *(int *)(param_4 + 0xa6c)),__dest,
            *(int *)(param_4 + 0x1270) - 0xc);
    RT_HMAC_SHA256(param_4 + 0x1a7d,0x20,*(undefined4 *)(param_1 + 0xa77c3c),param_3 + __n + -0xc,
                   &local_48,0x20);
  }
  iVar5 = memcmp(&local_50,&local_48,8);
  if (iVar5 == 0) {
    uVar8 = 0;
LAB_001f8c58:
    if (!bVar1) goto LAB_001f8d50;
  }
  else {
    if ((DebugLevel < 0) || (printk("ProcessMessageM3 --> HMAC not match\n"), DebugLevel < 3)) {
      uVar8 = 0xff;
      goto LAB_001f8c58;
    }
    printk("MD --> 0x%08x-%08x\n",
           local_48 << 0x18 | (local_48 >> 8 & 0xff) << 0x10 | (local_48 >> 0x10 & 0xff) << 8 |
           local_48 >> 0x18,
           local_44 << 0x18 | (local_44 >> 8 & 0xff) << 0x10 | (local_44 >> 0x10 & 0xff) << 8 |
           local_44 >> 0x18);
    if (2 < DebugLevel) {
      uVar8 = 0xff;
      printk("calculated --> 0x%08x-%08x\n",
             local_50 << 0x18 | (local_50 >> 8 & 0xff) << 0x10 | (local_50 >> 0x10 & 0xff) << 8 |
             local_50 >> 0x18,
             local_4c << 0x18 | (local_4c >> 8 & 0xff) << 0x10 | (local_4c >> 0x10 & 0xff) << 8 |
             local_4c >> 0x18);
      goto LAB_001f8c58;
    }
    if (bVar1) {
      return 0xfd;
    }
    uVar8 = 0xff;
LAB_001f8d50:
    if ((((uVar9 == 0) && (!bVar2)) && (!bVar3)) && (!bVar4)) goto LAB_001f8c64;
  }
  uVar8 = 0xfd;
LAB_001f8c64:
  if (2 < DebugLevel) {
    printk("ProcessMessageM3 :\n");
  }
  return uVar8;
}

