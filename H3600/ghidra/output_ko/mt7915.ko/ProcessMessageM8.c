// module: mt7915.ko
// function: ProcessMessageM8 @ 0x1fa624
// size: 1120 bytes
//

undefined4 ProcessMessageM8(int param_1,void *param_2,size_t param_3,int param_4)

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
  __dest = (uint *)(param_4 + 0x12e4);
  *(size_t *)(param_4 + 0x12e0) = param_3;
  memmove(__dest,param_2,param_3);
  puVar4 = __dest;
  if (4 < (int)param_3) {
    do {
      uVar3 = *puVar4;
      local_55._2_2_ = (ushort)(uVar3 >> 0x10);
      __n = (local_55._2_2_ & 0xff) << 8 | (uint)(local_55._2_2_ >> 8);
      uVar2 = (uVar3 & 0xff) << 8 | uVar3 >> 8 & 0xff;
      local_55 = uVar3;
      if ((int)param_3 < (int)(__n + 4)) {
        if (2 < DebugLevel) {
          printk("unexpected WSC IE Length(%u)\n",__n);
        }
        break;
      }
      __src = puVar4 + 1;
      if (uVar2 == 0x101a) {
        iVar1 = RTMPCompareMemory(param_4 + 0x1b40,__src,__n);
        if ((iVar1 != 0) && (2 < DebugLevel)) {
          printk("Rx M8 Compare enrollee nonce mismatched\n");
        }
      }
      else if (uVar2 < 0x101b) {
        if (uVar2 == 0x1005) {
          memcpy(&local_50,__src,__n);
        }
        else if (uVar2 == 0x1018) {
          if (0x10 < __n) {
            if (__n < 0x401) {
              memmove(local_5c,__src,__n);
              local_60 = 0x400;
              AES_CBC_Decrypt((int)local_5c + 0x10,__n - 0x10,param_4 + 0x1b0d,0x10,local_5c,0x10,
                              param_4 + 0x6d9,&local_60);
              if (2 < DebugLevel) {
                printk("M8 ApEncrSettings len = %d\n",local_60);
              }
              iVar1 = WscProcessCredential(param_1,param_4 + 0x6d9,local_60,param_4);
              if (iVar1 == 0) {
                if (local_5c != (void *)0x0) {
                  os_free_mem();
                }
                return 0xf;
              }
            }
            else if (2 < DebugLevel) {
              printk("ApEncrSettings array size is not enough, require %d\n",__n);
            }
          }
        }
        else {
LAB_001fa844:
          if (2 < DebugLevel) {
            printk("ProcessMessageM8 --> Unknown IE 0x%04x\n");
          }
        }
      }
      else if (uVar2 == 0x1022) {
        if (((char)puVar4[1] != '\f') && (-1 < DebugLevel)) {
          printk("Rx WPS Message Type mismatched %02x\n");
        }
      }
      else {
        if (uVar2 != 0x104a) goto LAB_001fa844;
        if ((*(char *)(param_4 + 0x70) != (char)puVar4[1]) && (-1 < DebugLevel)) {
          printk("Rx WPS Message Version mismatched %02x\n");
        }
      }
      param_3 = (param_3 - 4) - __n;
      puVar4 = (uint *)((int)__src + __n);
    } while (4 < (int)param_3);
    param_3 = *(size_t *)(param_4 + 0x12e0);
  }
  __n_00 = *(size_t *)(param_4 + 0xadc);
  if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
    memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_4 + 0xae0),__n_00);
    memmove((void *)(*(int *)(param_1 + 0xa77c3c) + *(int *)(param_4 + 0xadc)),__dest,
            *(int *)(param_4 + 0x12e0) - 0xc);
    RT_HMAC_SHA256(param_4 + 0x1aed,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n_00 + param_3 + -0xc
                   ,&local_48,0x20);
  }
  iVar1 = memcmp(&local_50,&local_48,8);
  if (iVar1 == 0) {
    uVar5 = 0;
LAB_001fa7d8:
    if (local_5c == (void *)0x0) goto LAB_001fa7e8;
  }
  else {
    if ((DebugLevel < 0) || (printk("ProcessMessageM8 --> HMAC not match\n"), DebugLevel < 3)) {
      uVar5 = 0xff;
      goto LAB_001fa7d8;
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
      goto LAB_001fa7d8;
    }
    if (local_5c == (void *)0x0) {
      return 0xff;
    }
    uVar5 = 0xff;
  }
  os_free_mem();
LAB_001fa7e8:
  if (2 < DebugLevel) {
    printk("ProcessMessageM8 :\n");
  }
  return uVar5;
}

