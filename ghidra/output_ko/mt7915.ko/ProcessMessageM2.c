// module: mt7915.ko
// function: ProcessMessageM2 @ 0x1f7a1c
// size: 2436 bytes
//

undefined4
ProcessMessageM2(int param_1,int param_2,void *param_3,size_t param_4,undefined4 param_5,
                char *param_6)

{
  bool bVar1;
  uint *__dest;
  uint uVar2;
  char cVar3;
  uint *puVar4;
  undefined4 uVar5;
  uint __n;
  char *__src;
  size_t __n_00;
  uint *__src_00;
  int iVar6;
  uint local_198;
  uint local_190;
  uint local_18c;
  char *local_184;
  uint *local_174;
  uint local_170;
  uint local_164;
  uint local_15c;
  uint local_156;
  uint local_152;
  uint local_14e;
  uint local_14a;
  undefined1 auStack_12e [32];
  uint local_10e;
  undefined4 local_10a;
  undefined4 local_106;
  undefined4 local_102;
  undefined4 local_fe;
  undefined2 local_fa;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
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
  
  local_156 = 0xffffffff;
  __dest = (uint *)(param_6 + 0x1274);
  local_152 = 0xffffffff;
  param_6[0x175] = '\0';
  RTMPZeroMemory(&local_14e,0x20);
  *(size_t *)(param_6 + 0x1270) = param_4;
  memmove(__dest,param_3,param_4);
  cVar3 = *(char *)(param_1 + 0x286285);
  if (cVar3 == '\x01') {
    MacTableLookup(param_1,param_6 + 0x186);
    cVar3 = *(char *)(param_1 + 0x286285);
  }
  if (cVar3 == '\0') {
    MacTableLookup2(param_1,param_6 + 0x186);
  }
  __memzero((void *)(param_2 + 0x2a5b),0xc6);
  if ((int)param_4 < 5) {
    local_170 = 0x2334;
    local_198 = 0x407;
    local_164 = 0x201e;
    local_190 = 0x1204;
    local_18c = 0x504;
    bVar1 = true;
  }
  else {
    local_198 = 0x407;
    local_170 = 0x2334;
    local_164 = 0x201e;
    local_190 = 0x1204;
    local_18c = 0x504;
    bVar1 = true;
    puVar4 = __dest;
    do {
      uVar2 = *puVar4;
      local_e8._2_2_ = (ushort)(uVar2 >> 0x10);
      __n = (local_e8._2_2_ & 0xff) << 8 | (uint)(local_e8._2_2_ >> 8);
      local_e8 = uVar2;
      if ((int)param_4 < (int)(__n + 4)) {
        if (2 < DebugLevel) {
          printk("unexpected WSC IE Length(%u)\n",__n);
        }
        break;
      }
      __src_00 = puVar4 + 1;
      switch((uVar2 & 0xff) << 8 | uVar2 >> 8 & 0xff) {
      case 0x1002:
        local_170 = local_170 ^ 4;
        *(short *)(param_6 + 0x278) = (short)puVar4[1];
        break;
      default:
        if (2 < DebugLevel) {
          printk("ProcessMessageM2 --> Unknown IE 0x%04x\n");
        }
        break;
      case 0x1004:
        local_170 = local_170 ^ 0x10;
        *(short *)(param_6 + 0x1c6) = (short)puVar4[1];
        break;
      case 0x1005:
        local_170 = local_170 ^ 0x20;
        memcpy(&local_156,__src_00,__n);
        break;
      case 0x1008:
        local_170 = local_170 ^ 0x100;
        *(short *)(param_6 + 0x1cc) = (short)puVar4[1];
        break;
      case 0x1009:
        local_170 = local_170 ^ 0x200;
        *(short *)(param_6 + 0x27c) = (short)puVar4[1];
        break;
      case 0x100d:
        local_170 = local_170 ^ 0x2000;
        param_6[0x1ca] = (char)puVar4[1];
        break;
      case 0x1010:
        local_198 = local_198 ^ 1;
        *(short *)(param_6 + 0x1c8) = (short)puVar4[1];
        break;
      case 0x1011:
        local_198 = local_198 ^ 2;
        memmove(param_6 + 0x18c,__src_00,__n);
        memmove((void *)(param_2 + 0x2a5b),__src_00,__n);
        break;
      case 0x1012:
        local_198 = local_198 ^ 4;
        *(short *)(param_6 + 0x27a) = (short)puVar4[1];
        break;
      case 0x101a:
        iVar6 = RTMPCompareMemory(param_6 + 0x1af0,__src_00,__n);
        if ((iVar6 != 0) && (2 < DebugLevel)) {
          printk("Rx M2 Compare enrollee nonce mismatched\n");
        }
        local_198 = local_198 ^ 0x400;
        break;
      case 0x1021:
        memmove(param_6 + 0x1cf,__src_00,__n);
        local_164 = local_164 ^ 2;
        memmove((void *)(param_2 + 0x2a7b),__src_00,__n);
        break;
      case 0x1022:
        if (((char)puVar4[1] != '\x05') && (-1 < DebugLevel)) {
          printk("Rx WPS Message Type mismatched %02x\n");
        }
        local_164 = local_164 ^ 4;
        break;
      case 0x1023:
        memmove(param_6 + 0x20f,__src_00,__n);
        local_164 = local_164 ^ 8;
        memmove((void *)(param_2 + 0x2abb),__src_00,__n);
        break;
      case 0x1024:
        memmove(param_6 + 0x22f,__src_00,__n);
        local_164 = local_164 ^ 0x10;
        memmove((void *)(param_2 + 0x2adb),__src_00,__n);
        break;
      case 0x102d:
        local_164 = local_164 ^ 0x2000;
        *(uint *)(param_6 + 0x270) = puVar4[1];
        break;
      case 0x1032:
        local_190 = local_190 ^ 4;
        memmove(param_6 + 0x469,__src_00,__n);
        break;
      case 0x1039:
        local_190 = local_190 ^ 0x200;
        memmove(param_6 + 0x1ae0,__src_00,__n);
        break;
      case 0x103c:
        param_6[0x26f] = (char)puVar4[1];
        local_190 = local_190 ^ 0x1000;
        break;
      case 0x1042:
        memmove(param_6 + 0x24f,__src_00,__n);
        local_18c = local_18c ^ 4;
        memmove((void *)(param_2 + 0x2afb),__src_00,__n);
        break;
      case 0x1048:
        local_18c = local_18c ^ 0x100;
        memmove(param_6 + 0x176,__src_00,__n);
        break;
      case 0x1049:
        if (*(char *)(param_2 + 0x2b31) != '\0') {
          local_10e = local_10e & 0xffffff00;
          WscParseV2SubItem(0,__src_00,__n,param_6 + 0x175,&local_10e);
          if (2 < DebugLevel) {
            printk("ProcessMessageM2 --> Version2 = %x\n",param_6[0x175]);
          }
        }
        break;
      case 0x104a:
        if ((*param_6 != (char)puVar4[1]) && (-1 < DebugLevel)) {
          printk("Rx WPS Message Version mismatched %02x\n");
        }
        local_18c = local_18c ^ 0x400;
        break;
      case 0x1054:
        bVar1 = (bool)(bVar1 ^ 1);
        memmove(param_6 + 0x1ac,__src_00,__n);
      }
      param_4 = (param_4 - 4) - __n;
      puVar4 = (uint *)((int)__src_00 + __n);
      *(undefined4 *)(param_2 + 0x2b1b) = *(undefined4 *)(param_2 + 0x1f6);
      *(undefined2 *)(param_2 + 0x2b1f) = *(undefined2 *)(param_2 + 0x1fa);
    } while (4 < (int)param_4);
  }
  local_174 = &local_10e;
  local_184 = param_6 + 0x469;
  __src = param_6 + 0x529;
  local_15c = 0xc0;
  __memzero(__src,0xc0);
  DH_SecretKey_Generate(local_184,0xc0,WPS_DH_P_VALUE,0xc0,param_6 + 0x2e8,0xc0,__src,&local_15c);
  if (local_15c < 0xc0) {
    iVar6 = 0xc0 - local_15c;
    __memzero(&local_e8,iVar6);
    uVar2 = iVar6 + local_15c;
    memcpy((void *)((int)&local_e8 + iVar6),__src,local_15c);
    memcpy(__src,&local_e8,0xc0);
    local_15c = uVar2;
    if (2 < DebugLevel) {
      printk("%s: Do zero padding!\n","ProcessMessageM2");
    }
  }
  RT_SHA256(__src,0xc0,auStack_12e);
  local_10e = *(uint *)(param_6 + 0x1af0);
  local_fe = *(undefined4 *)(param_6 + 0x12);
  local_10a = *(undefined4 *)(param_6 + 0x1af4);
  local_102 = *(undefined4 *)(param_6 + 0x1afc);
  local_fa = *(undefined2 *)(param_6 + 0x16);
  local_106 = *(undefined4 *)(param_6 + 0x1af8);
  local_f8 = *(undefined4 *)(param_6 + 0x1ae0);
  local_ec = *(undefined4 *)(param_6 + 0x1aec);
  local_f4 = *(undefined4 *)(param_6 + 0x1ae4);
  local_f0 = *(undefined4 *)(param_6 + 0x1ae8);
  RT_HMAC_SHA256(auStack_12e,0x20,local_174,0x26,&local_14e,0x20);
  WscDeriveKey(&local_14e,0x20,_LANCHOR1,0x24,&local_e8,0x280);
  *(uint *)(param_6 + 0x1a7d) = local_e8;
  *(undefined4 *)(param_6 + 0x1a81) = uStack_e4;
  *(undefined4 *)(param_6 + 0x1a85) = uStack_e0;
  *(undefined4 *)(param_6 + 0x1a89) = uStack_dc;
  *(undefined4 *)(param_6 + 0x1a8d) = local_d8;
  *(undefined4 *)(param_6 + 0x1a91) = uStack_d4;
  *(undefined4 *)(param_6 + 0x1a95) = uStack_d0;
  *(undefined4 *)(param_6 + 0x1a99) = uStack_cc;
  *(undefined4 *)(param_6 + 0x1a9d) = local_c8;
  *(undefined4 *)(param_6 + 0x1aa1) = uStack_c4;
  *(undefined4 *)(param_6 + 0x1aa5) = uStack_c0;
  *(undefined4 *)(param_6 + 0x1aa9) = uStack_bc;
  *(undefined4 *)(param_6 + 0x1aad) = local_b8;
  *(undefined4 *)(param_6 + 0x1ab1) = uStack_b4;
  *(undefined4 *)(param_6 + 0x1ab5) = uStack_b0;
  *(undefined4 *)(param_6 + 0x1ab9) = uStack_ac;
  *(undefined4 *)(param_6 + 0x1abd) = local_a8;
  *(undefined4 *)(param_6 + 0x1ac1) = uStack_a4;
  *(undefined4 *)(param_6 + 0x1ac5) = uStack_a0;
  *(undefined4 *)(param_6 + 0x1ac9) = uStack_9c;
  __n_00 = *(size_t *)(param_6 + 0xa6c);
  iVar6 = *(int *)(param_6 + 0x1270);
  if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
    memmove(*(void **)(param_1 + 0xa77c3c),param_6 + 0xa70,__n_00);
    memmove((void *)(*(int *)(param_1 + 0xa77c3c) + *(int *)(param_6 + 0xa6c)),__dest,
            *(int *)(param_6 + 0x1270) - 0xc);
    RT_HMAC_SHA256(param_6 + 0x1a7d,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n_00 + iVar6 + -0xc,
                   &local_14e,0x20);
  }
  iVar6 = memcmp(&local_156,&local_14e,8);
  if (iVar6 == 0) {
    uVar5 = 0;
LAB_001f7fb8:
    if (local_170 == 0) goto LAB_001f834c;
  }
  else {
    if ((DebugLevel < 0) || (printk("ProcessMessageM2 --> HMAC not match\n"), DebugLevel < 3)) {
      uVar5 = 0xff;
      goto LAB_001f7fb8;
    }
    printk("MD --> 0x%08x-%08x\n",
           local_14e << 0x18 | (local_14e >> 8 & 0xff) << 0x10 | (local_14e >> 0x10 & 0xff) << 8 |
           local_14e >> 0x18,
           local_14a << 0x18 | (local_14a >> 8 & 0xff) << 0x10 | (local_14a >> 0x10 & 0xff) << 8 |
           local_14a >> 0x18);
    if (2 < DebugLevel) {
      uVar5 = 0xff;
      printk("calculated --> 0x%08x-%08x\n",
             local_156 << 0x18 | (local_156 >> 8 & 0xff) << 0x10 | (local_156 >> 0x10 & 0xff) << 8 |
             local_156 >> 0x18,
             local_152 << 0x18 | (local_152 >> 8 & 0xff) << 0x10 | (local_152 >> 0x10 & 0xff) << 8 |
             local_152 >> 0x18);
      goto LAB_001f7fb8;
    }
    if (local_170 != 0) {
      return 0xfd;
    }
    uVar5 = 0xff;
LAB_001f834c:
    if ((((local_198 == 0) && (local_164 == 0)) && (local_190 == 0)) &&
       ((local_18c == 0 && (!bVar1)))) goto LAB_001f7fc8;
  }
  uVar5 = 0xfd;
LAB_001f7fc8:
  if (2 < DebugLevel) {
    printk("ProcessMessageM2 :\n");
  }
  return uVar5;
}

