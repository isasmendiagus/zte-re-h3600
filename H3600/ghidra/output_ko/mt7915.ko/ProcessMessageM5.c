// module: mt7915.ko
// function: ProcessMessageM5 @ 0x1f9580
// size: 1636 bytes
//

undefined4
ProcessMessageM5(int param_1,undefined4 param_2,void *param_3,size_t param_4,char *param_5)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  void *__dest;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  uint __n;
  uint *__src;
  size_t __n_00;
  uint *__dest_00;
  size_t local_8c;
  undefined4 local_78;
  void *local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  undefined4 local_48;
  
  local_70 = 0xffffffff;
  local_6c = 0xffffffff;
  local_74 = (void *)0x0;
  RTMPZeroMemory(&local_68,0x20);
  os_alloc_mem(0,&local_74,0x200);
  __dest = local_74;
  if (local_74 == (void *)0x0) {
    uVar6 = 0xfc;
  }
  else {
    __dest_00 = (uint *)(param_5 + 0x1274);
    *(size_t *)(param_5 + 0x1270) = param_4;
    memmove(__dest_00,param_3,param_4);
    if ((int)param_4 < 5) {
      bVar1 = true;
      bVar2 = true;
      bVar3 = true;
      bVar4 = true;
      bVar5 = true;
      local_8c = param_4;
    }
    else {
      bVar1 = true;
      bVar2 = true;
      bVar3 = true;
      bVar4 = true;
      bVar5 = true;
      puVar10 = __dest_00;
      do {
        while( true ) {
          uVar7 = *puVar10;
          local_48._2_2_ = (ushort)(uVar7 >> 0x10);
          __n = (local_48._2_2_ & 0xff) << 8 | (uint)(local_48._2_2_ >> 8);
          uVar9 = (uVar7 & 0xff) << 8 | uVar7 >> 8 & 0xff;
          local_48 = uVar7;
          if ((int)param_4 < (int)(__n + 4)) {
            if (2 < DebugLevel) {
              printk("unexpected WSC IE Length(%u)\n",__n);
            }
            local_8c = *(size_t *)(param_5 + 0x1270);
            goto LAB_001f96fc;
          }
          __src = puVar10 + 1;
          if (uVar9 != 0x1022) break;
          if (((char)puVar10[1] != '\t') && (-1 < DebugLevel)) {
            printk("Rx WPS Message Type mismatched %02x\n");
          }
          bVar3 = (bool)(bVar3 ^ 1);
joined_r0x001f9aac:
          param_4 = (param_4 - 4) - __n;
          puVar10 = (uint *)((int)__src + __n);
          if ((int)param_4 < 5) goto LAB_001f96e4;
        }
        if (uVar9 < 0x1023) {
          if (uVar9 == 0x1005) {
            bVar1 = (bool)(bVar1 ^ 1);
            memcpy(&local_70,__src,__n);
          }
          else if (uVar9 == 0x1018) {
            if (0x10 < __n) {
              if (__n < 0x201) {
                memmove(local_74,__src,__n);
                local_78 = 0x400;
                AES_CBC_Decrypt((int)local_74 + 0x10,__n - 0x10,param_5 + 0x1a9d,0x10,local_74,0x10,
                                param_5 + 0x669,&local_78);
                if (2 < DebugLevel) {
                  printk("M5 ApEncrSettings len = %d\n",local_78);
                }
                bVar2 = (bool)(bVar2 ^ 1);
                FUN_001f2ce8(param_1,param_5 + 0x669,local_78,param_2);
                goto joined_r0x001f9aac;
              }
              if (2 < DebugLevel) {
                printk("ApEncrSettings array size is not enough, require %d\n",__n);
              }
            }
          }
          else {
LAB_001f98e8:
            if (2 < DebugLevel) {
              printk("ProcessMessageM4 --> Unknown IE 0x%04x\n");
            }
          }
        }
        else {
          if (uVar9 != 0x1039) {
            if (uVar9 != 0x104a) goto LAB_001f98e8;
            if ((*param_5 != (char)puVar10[1]) && (-1 < DebugLevel)) {
              printk("Rx WPS Message Version mismatched %02x\n");
            }
            bVar5 = (bool)(bVar5 ^ 1);
            goto joined_r0x001f9aac;
          }
          iVar8 = RTMPCompareMemory(param_5 + 0x1ae0,__src,__n);
          if ((iVar8 != 0) && (2 < DebugLevel)) {
            printk("Rx M5 Compare Registrar nonce mismatched\n");
          }
          bVar4 = (bool)(bVar4 ^ 1);
        }
        param_4 = (param_4 - 4) - __n;
        puVar10 = (uint *)((int)__src + __n);
      } while (4 < (int)param_4);
LAB_001f96e4:
      local_8c = *(size_t *)(param_5 + 0x1270);
    }
LAB_001f96fc:
    __n_00 = *(size_t *)(param_5 + 0xa6c);
    if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
      memmove(*(void **)(param_1 + 0xa77c3c),param_5 + 0xa70,__n_00);
      memmove((void *)(*(int *)(param_1 + 0xa77c3c) + *(int *)(param_5 + 0xa6c)),__dest_00,
              *(int *)(param_5 + 0x1270) - 0xc);
    }
    memmove(__dest,param_5 + 0x1b60,0x10);
    memmove((void *)((int)__dest + 0x10),param_5 + 0x1b00,0x10);
    memmove((void *)((int)__dest + 0x20),param_5 + 0x3a9,0xc0);
    memmove((void *)((int)__dest + 0xe0),param_5 + 0x469,0xc0);
    RT_HMAC_SHA256(param_5 + 0x1a7d,0x20,__dest,0x1a0,&local_48,0x20);
    iVar8 = RTMPCompareMemory(param_5 + 0x1b20,&local_48,0x20);
    if (iVar8 == 0) {
      if (*(int *)(param_1 + 0xa77c3c) != 0) {
        RT_HMAC_SHA256(param_5 + 0x1a7d,0x20,*(int *)(param_1 + 0xa77c3c),local_8c + __n_00 + -0xc,
                       &local_68,0x20);
      }
      iVar8 = memcmp(&local_70,&local_68,8);
      if (iVar8 == 0) {
        uVar6 = 0;
      }
      else if (((DebugLevel < 0) ||
               (printk("ProcessMessageM5 --> HMAC not match\n"), DebugLevel < 3)) ||
              (printk("MD --> 0x%08x-%08x\n",
                      local_68 << 0x18 | (local_68 >> 8 & 0xff) << 0x10 |
                      (local_68 >> 0x10 & 0xff) << 8 | local_68 >> 0x18,
                      local_64 << 0x18 | (local_64 >> 8 & 0xff) << 0x10 |
                      (local_64 >> 0x10 & 0xff) << 8 | local_64 >> 0x18), DebugLevel < 3)) {
        uVar6 = 0xff;
      }
      else {
        uVar6 = 0xff;
        printk("calculated --> 0x%08x-%08x\n",
               local_70 << 0x18 | (local_70 >> 8 & 0xff) << 0x10 | (local_70 >> 0x10 & 0xff) << 8 |
               local_70 >> 0x18,
               local_6c << 0x18 | (local_6c >> 8 & 0xff) << 0x10 | (local_6c >> 0x10 & 0xff) << 8 |
               local_6c >> 0x18);
      }
      if (((bVar1) || (bVar2)) || ((bVar3 || (bVar4)))) {
        uVar6 = 0xfd;
      }
      else if (bVar5) {
        uVar6 = 0xfd;
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("ProcessMessageM5 --> EHash1 not matched\n");
      }
      uVar6 = 0xfe;
      param_5[0x108] = -2;
      param_5[0x109] = '\0';
    }
    if (local_74 != (void *)0x0) {
      os_free_mem();
    }
    if (2 < DebugLevel) {
      printk("ProcessMessageM5 :\n");
    }
  }
  return uVar6;
}

