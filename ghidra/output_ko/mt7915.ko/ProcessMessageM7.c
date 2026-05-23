// module: mt7915.ko
// function: ProcessMessageM7 @ 0x1fa194
// size: 1164 bytes
//

undefined4 ProcessMessageM7(int param_1,int param_2,void *param_3,size_t param_4,char *param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint __n;
  undefined4 uVar5;
  uint *__src;
  size_t __n_00;
  uint *__dest;
  undefined4 local_60;
  void *local_5c;
  undefined4 local_55;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  
  local_50 = 0xffffffff;
  local_4c = 0xffffffff;
  local_5c = (void *)0x0;
  RTMPZeroMemory(&local_48,0x20);
  os_alloc_mem(0,&local_5c,0x400);
  if (local_5c == (void *)0x0) {
    return 0xfc;
  }
  __dest = (uint *)(param_5 + 0x1274);
  *(size_t *)(param_5 + 0x1270) = param_4;
  memmove(__dest,param_3,param_4);
  if (4 < (int)param_4) {
    puVar4 = __dest;
    do {
      while( true ) {
        uVar3 = *puVar4;
        local_55._2_2_ = (ushort)(uVar3 >> 0x10);
        __n = (local_55._2_2_ & 0xff) << 8 | (uint)(local_55._2_2_ >> 8);
        uVar2 = (uVar3 & 0xff) << 8 | uVar3 >> 8 & 0xff;
        local_55 = uVar3;
        if ((int)param_4 < (int)(__n + 4)) {
          if (2 < DebugLevel) {
            printk("unexpected WSC IE Length(%u)\n",__n);
          }
          goto LAB_001fa2bc;
        }
        __src = puVar4 + 1;
        if (uVar2 != 0x1022) break;
        if (((char)puVar4[1] != '\v') && (-1 < DebugLevel)) {
          printk("Rx WPS Message Type mismatched %02x\n");
        }
joined_r0x001fa3f0:
        param_4 = (param_4 - 4) - __n;
        puVar4 = (uint *)((int)__src + __n);
        if ((int)param_4 < 5) goto LAB_001fa2bc;
      }
      if (0x1022 < uVar2) {
        if (uVar2 == 0x1039) {
          iVar1 = RTMPCompareMemory(param_5 + 0x1ae0,__src,__n);
          if ((iVar1 != 0) && (2 < DebugLevel)) {
            printk("Rx M5 Compare Registrar nonce mismatched\n");
          }
        }
        else {
          if (uVar2 != 0x104a) goto LAB_001fa3b8;
          if ((*param_5 != (char)puVar4[1]) && (-1 < DebugLevel)) {
            printk("Rx WPS Message Version mismatched %02x\n");
          }
        }
        goto joined_r0x001fa3f0;
      }
      if (uVar2 == 0x1005) {
        memcpy(&local_50,__src,__n);
        goto joined_r0x001fa3f0;
      }
      if (uVar2 != 0x1018) {
LAB_001fa3b8:
        if (2 < DebugLevel) {
          printk("ProcessMessageM7 --> Unknown IE 0x%04x\n");
        }
        goto joined_r0x001fa3f0;
      }
      if (__n < 0x11) goto joined_r0x001fa3f0;
      if (0x400 < __n) {
        if (2 < DebugLevel) {
          printk("ApEncrSettings array size is not enough, require %d\n",__n);
        }
        goto joined_r0x001fa3f0;
      }
      memmove(local_5c,__src,__n);
      local_60 = 0x400;
      AES_CBC_Decrypt((int)local_5c + 0x10,__n - 0x10,param_5 + 0x1a9d,0x10,local_5c,0x10,
                      param_5 + 0x669,&local_60);
      if (2 < DebugLevel) {
        printk("M7 ApEncrSettings len = %d\n",local_60);
      }
      if (*(char *)(param_1 + 0x286285) == '\0') {
        RTMPZeroMemory(param_2 + 0x23e0,0x3a8);
      }
      param_4 = (param_4 - 4) - __n;
      FUN_001f2ce8(param_1,param_5 + 0x669,local_60,param_2);
      puVar4 = (uint *)((int)__src + __n);
    } while (4 < (int)param_4);
LAB_001fa2bc:
    param_4 = *(size_t *)(param_5 + 0x1270);
  }
  __n_00 = *(size_t *)(param_5 + 0xa6c);
  if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
    memmove(*(void **)(param_1 + 0xa77c3c),param_5 + 0xa70,__n_00);
    memmove((void *)(*(int *)(param_1 + 0xa77c3c) + *(int *)(param_5 + 0xa6c)),__dest,
            *(int *)(param_5 + 0x1270) - 0xc);
    RT_HMAC_SHA256(param_5 + 0x1a7d,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n_00 + param_4 + -0xc
                   ,&local_48,0x20);
  }
  iVar1 = memcmp(&local_50,&local_48,8);
  if (iVar1 == 0) {
    uVar5 = 0;
LAB_001fa34c:
    if (local_5c == (void *)0x0) goto LAB_001fa35c;
  }
  else {
    if ((DebugLevel < 0) || (printk("ProcessMessageM7 --> HMAC not match\n"), DebugLevel < 3)) {
      uVar5 = 0xff;
      goto LAB_001fa34c;
    }
    printk("MD --> 0x%08x-%08x\n",
           local_48 << 0x18 | (local_48 >> 8 & 0xff) << 0x10 | (local_48 >> 0x10 & 0xff) << 8 |
           local_48 >> 0x18,
           local_44 << 0x18 | (local_44 >> 8 & 0xff) << 0x10 | (local_44 >> 0x10 & 0xff) << 8 |
           local_44 >> 0x18);
    if (2 < DebugLevel) {
      uVar5 = 0xff;
      printk("calculated --> 0x%08x-%08x\n",
             local_50 << 0x18 | (local_50 >> 8 & 0xff) << 0x10 | (local_50 >> 0x10 & 0xff) << 8 |
             local_50 >> 0x18,
             local_4c << 0x18 | (local_4c >> 8 & 0xff) << 0x10 | (local_4c >> 0x10 & 0xff) << 8 |
             local_4c >> 0x18);
      goto LAB_001fa34c;
    }
    if (local_5c == (void *)0x0) {
      return 0xff;
    }
    uVar5 = 0xff;
  }
  os_free_mem();
LAB_001fa35c:
  if (2 < DebugLevel) {
    printk("ProcessMessageM7 :\n");
  }
  return uVar5;
}

