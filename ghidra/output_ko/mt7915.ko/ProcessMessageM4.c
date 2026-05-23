// module: mt7915.ko
// function: ProcessMessageM4 @ 0x1f8e80
// size: 1508 bytes
//

undefined4
ProcessMessageM4(int param_1,undefined4 param_2,void *param_3,size_t param_4,char *param_5)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  void *__dest;
  uint uVar4;
  int iVar5;
  uint *__dest_00;
  uint *puVar6;
  uint __n;
  undefined4 uVar7;
  uint *__src;
  size_t __n_00;
  uint uVar8;
  uint local_a4;
  char *local_94;
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
    return 0xfc;
  }
  __dest_00 = (uint *)(param_5 + 0x1274);
  *(size_t *)(param_5 + 0x1270) = param_4;
  memmove(__dest_00,param_3,param_4);
  if (4 < (int)param_4) {
    uVar8 = 0x6000;
    bVar1 = true;
    local_a4 = 0x500;
    bVar2 = true;
    bVar3 = true;
    puVar6 = __dest_00;
LAB_001f8f6c:
    do {
      uVar4 = *puVar6;
      local_48._2_2_ = (ushort)(uVar4 >> 0x10);
      __n = (local_48._2_2_ & 0xff) << 8 | (uint)(local_48._2_2_ >> 8);
      local_48 = uVar4;
      if ((int)param_4 < (int)(__n + 4)) {
        if (2 < DebugLevel) {
          printk("unexpected WSC IE Length(%u)\n",__n);
        }
        break;
      }
      __src = puVar6 + 1;
      switch((uVar4 & 0xff) << 8 | uVar4 >> 8 & 0xff) {
      case 0x1005:
        bVar1 = (bool)(bVar1 ^ 1);
        memcpy(&local_70,__src,__n);
        break;
      default:
        if (2 < DebugLevel) {
          printk("ProcessMessageM4 --> Unknown IE 0x%04x\n");
        }
        break;
      case 0x1018:
        if (0x10 < __n) {
          if (__n < 0x201) {
            memmove(local_74,__src,__n);
            local_78 = 0x400;
            AES_CBC_Decrypt((int)local_74 + 0x10,__n - 0x10,param_5 + 0x1a9d,0x10,local_74,0x10,
                            param_5 + 0x669,&local_78);
            if (2 < DebugLevel) {
              printk("M4 ApEncrSettings len = %d\n",local_78);
            }
            local_a4 = local_a4 ^ 0x100;
            FUN_001f2ce8(param_1,param_5 + 0x669,local_78,param_2);
          }
          else if (2 < DebugLevel) {
            printk("ApEncrSettings array size is not enough, require %d\n",__n);
          }
        }
        break;
      case 0x101a:
        iVar5 = RTMPCompareMemory(param_5 + 0x1ad0,__src,__n);
        if ((iVar5 != 0) && (2 < DebugLevel)) {
          printk("Rx M4 Compare enrollee nonce mismatched\n");
        }
        local_a4 = local_a4 ^ 0x400;
        break;
      case 0x1022:
        if (((char)puVar6[1] != '\b') && (-1 < DebugLevel)) {
          printk("Rx WPS Message Type mismatched %02x\n");
        }
        bVar2 = (bool)(bVar2 ^ 1);
        break;
      case 0x103d:
        uVar8 = uVar8 ^ 0x2000;
        memmove(param_5 + 0x1b80,__src,__n);
        break;
      case 0x103e:
        uVar8 = uVar8 ^ 0x4000;
        memmove(param_5 + 0x1ba0,__src,__n);
        break;
      case 0x104a:
        goto switchD_001f8fac_caseD_104a;
      }
      param_4 = (param_4 - 4) - __n;
      puVar6 = (uint *)((int)__src + __n);
    } while (4 < (int)param_4);
    goto LAB_001f9104;
  }
  uVar8 = 0x6000;
  bVar1 = true;
  local_a4 = 0x500;
  bVar2 = true;
  bVar3 = true;
LAB_001f9104:
  local_94 = param_5 + 0x1b80;
  memmove(__dest,param_5 + 0x1bc0,0x10);
  memmove((void *)((int)__dest + 0x10),param_5 + 0x1b00,0x10);
  memmove((void *)((int)__dest + 0x20),param_5 + 0x3a9,0xc0);
  memmove((void *)((int)__dest + 0xe0),param_5 + 0x469,0xc0);
  RT_HMAC_SHA256(param_5 + 0x1a7d,0x20,__dest,0x1a0,&local_48,0x20);
  iVar5 = RTMPCompareMemory(local_94,&local_48,0x20);
  if (iVar5 == 0) {
    __n_00 = *(size_t *)(param_5 + 0xa6c);
    iVar5 = *(int *)(param_5 + 0x1270);
    if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
      memmove(*(void **)(param_1 + 0xa77c3c),param_5 + 0xa70,__n_00);
      memmove((void *)(*(int *)(param_1 + 0xa77c3c) + *(int *)(param_5 + 0xa6c)),__dest_00,
              *(int *)(param_5 + 0x1270) - 0xc);
      RT_HMAC_SHA256(param_5 + 0x1a7d,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n_00 + iVar5 + -0xc
                     ,&local_68,0x20);
    }
    iVar5 = memcmp(&local_70,&local_68,8);
    if (iVar5 == 0) {
      uVar7 = 0;
    }
    else if (((DebugLevel < 0) || (printk("ProcessMessageM4 --> HMAC not match\n"), DebugLevel < 3))
            || (printk("MD --> 0x%08x-%08x\n",
                       local_68 << 0x18 | (local_68 >> 8 & 0xff) << 0x10 |
                       (local_68 >> 0x10 & 0xff) << 8 | local_68 >> 0x18,
                       local_64 << 0x18 | (local_64 >> 8 & 0xff) << 0x10 |
                       (local_64 >> 0x10 & 0xff) << 8 | local_64 >> 0x18), DebugLevel < 3)) {
      uVar7 = 0xff;
    }
    else {
      uVar7 = 0xff;
      printk("calculated --> 0x%08x-%08x\n",
             local_70 << 0x18 | (local_70 >> 8 & 0xff) << 0x10 | (local_70 >> 0x10 & 0xff) << 8 |
             local_70 >> 0x18,
             local_6c << 0x18 | (local_6c >> 8 & 0xff) << 0x10 | (local_6c >> 0x10 & 0xff) << 8 |
             local_6c >> 0x18);
    }
    if (((bVar1) || (local_a4 != 0)) || ((bVar2 || (uVar8 != 0)))) {
      uVar7 = 0xfd;
    }
    else if (bVar3) {
      uVar7 = 0xfd;
    }
LAB_001f938c:
    if (local_74 == (void *)0x0) goto LAB_001f91ac;
  }
  else {
    if (2 < DebugLevel) {
      uVar7 = 0x12;
      printk("ProcessMessageM4 --> RHash1 not matched\n");
      goto LAB_001f938c;
    }
    if (local_74 == (void *)0x0) {
      return 0x12;
    }
    uVar7 = 0x12;
  }
  os_free_mem();
LAB_001f91ac:
  if (2 < DebugLevel) {
    printk("ProcessMessageM4 :\n");
  }
  return uVar7;
switchD_001f8fac_caseD_104a:
  if ((*param_5 != (char)puVar6[1]) && (-1 < DebugLevel)) {
    printk("Rx WPS Message Version mismatched %02x\n");
  }
  param_4 = (param_4 - 4) - __n;
  puVar6 = (uint *)((int)__src + __n);
  bVar3 = (bool)(bVar3 ^ 1);
  if ((int)param_4 < 5) goto LAB_001f9104;
  goto LAB_001f8f6c;
}

