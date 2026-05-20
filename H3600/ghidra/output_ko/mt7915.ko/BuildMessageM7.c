// module: mt7915.ko
// function: BuildMessageM7 @ 0x1f5f5c
// size: 1320 bytes
//

size_t BuildMessageM7(int param_1,int param_2,void *param_3)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  size_t sVar4;
  uint uVar5;
  ushort uVar6;
  uint uVar7;
  size_t __n;
  int iVar8;
  int *local_168;
  ushort local_15a;
  size_t local_158;
  void *local_154;
  int local_150;
  int local_14c;
  undefined1 local_148 [32];
  undefined1 auStack_128 [260];
  
  iVar8 = 0;
  local_150 = 0;
  local_158 = 0;
  local_154 = param_3;
  os_alloc_mem(0,&local_150,0x200);
  sVar4 = 0;
  if (local_150 != 0) {
    if (*(char *)(param_1 + 0x286285) != '\x01') {
      if (*(char *)(param_1 + 0x286285) == '\0') {
        iVar8 = 2;
      }
      else {
        iVar8 = 0xff;
      }
    }
    iVar1 = AppendWSCTLV(0x104a,local_154,param_2 + 0x70,0);
    local_148[0] = 0xb;
    local_154 = (void *)((int)local_154 + iVar1);
    local_158 = local_158 + iVar1;
    iVar1 = AppendWSCTLV(0x1022,local_154,local_148,0);
    local_154 = (void *)((int)local_154 + iVar1);
    local_158 = local_158 + iVar1;
    iVar1 = AppendWSCTLV(0x1039,local_154,param_2 + 0x1b50,0);
    local_154 = (void *)((int)local_154 + iVar1);
    local_158 = local_158 + iVar1;
    uVar2 = AppendWSCTLV(0x1017,auStack_128,param_2 + 0x1be0,0);
    if ((iVar8 == 0) && (*(byte *)(param_2 + 0x1c54) < 0x30)) {
      WscCreateProfileFromCfg(param_1,0x80,param_2,param_2 + 0x1c90);
      local_15a = *(ushort *)(param_2 + 0x1cbc);
      uVar5 = (uint)local_15a;
      uVar6 = *(ushort *)(param_2 + 0x1cbe);
      uVar7 = (uint)uVar6;
      local_14c = CONCAT22(local_14c._2_2_,uVar6);
      if (*(char *)(param_2 + 0x1e5) == '\0') {
        if (uVar5 == 0x22) {
          local_15a = 0x20;
        }
        if (uVar7 == 0xc) {
          uVar5 = (uint)local_15a;
          uVar6 = 0x800;
        }
        else {
          uVar6 = (ushort)((uVar7 & 0xff) << 8) | uVar6 >> 8;
          uVar5 = (uint)local_15a;
        }
      }
      else {
        uVar6 = (ushort)((uVar7 & 0xff) << 8) | uVar6 >> 8;
      }
      local_15a = (ushort)((uVar5 & 0xff) << 8) | (ushort)(uVar5 >> 8);
                    /* WARNING: Ignoring partial resolution of indirect */
      local_14c._0_2_ = uVar6;
      if (uVar2 < 0xfc) {
        iVar8 = AppendWSCTLV(0x1045,auStack_128 + uVar2,param_2 + 0x1c9c,
                             *(uint *)(param_2 + 0x1c98) & 0xffff);
        uVar2 = uVar2 + iVar8;
        if (uVar2 < 0xf8) {
          iVar8 = AppendWSCTLV(0x1020,auStack_128 + uVar2,param_2 + 0x1d02,0);
          uVar2 = uVar2 + iVar8;
          if (uVar2 < 0xf4) {
            iVar8 = AppendWSCTLV(0x1003,auStack_128 + uVar2,&local_15a,0);
            uVar2 = uVar2 + iVar8;
            if (uVar2 < 0xf0) {
              iVar8 = AppendWSCTLV(0x100f,auStack_128 + uVar2,&local_14c,0);
              uVar2 = uVar2 + iVar8;
              if (uVar2 < 0xec) {
                iVar8 = AppendWSCTLV(0x1028,auStack_128 + uVar2,param_2 + 0x1d08,0);
                uVar2 = uVar2 + iVar8;
                if (uVar2 < 0xe8) {
                  iVar8 = AppendWSCTLV(0x1027,auStack_128 + uVar2,param_2 + 0x1cc0,
                                       *(undefined2 *)(param_2 + 0x1d00));
                  uVar2 = uVar2 + iVar8;
                }
              }
            }
          }
        }
      }
    }
    local_168 = &local_14c;
    RT_HMAC_SHA256(param_2 + 0x1aed,0x20,auStack_128,uVar2,local_148,0x20);
    if (uVar2 < 0xe4) {
      iVar8 = AppendWSCTLV(0x101e,auStack_128 + uVar2,local_148,0);
      uVar2 = iVar8 + uVar2;
    }
    local_14c = 0x1f0;
    AES_CBC_Encrypt(auStack_128,uVar2,param_2 + 0x1b0d,0x10,local_150,0x10,local_150 + 0x10,
                    local_168);
    iVar8 = AppendWSCTLV(0x1018,local_154,local_150,local_14c + 0x10U & 0xffff);
    local_154 = (void *)((int)local_154 + iVar8);
    local_158 = iVar8 + local_158;
    if (((*(char *)(param_2 + 0x2b31) != '\0') &&
        (WscGenV2Msg(param_2,0,0,0,&local_154,&local_158), *(int *)(param_2 + 0x2b28) != 0)) &&
       (*(short *)(param_2 + 0x2b26) != 0)) {
      iVar8 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_154);
      local_154 = (void *)((int)local_154 + iVar8);
      local_158 = iVar8 + local_158;
    }
    sVar4 = local_158;
    __n = *(size_t *)(param_2 + 0x12e0);
    if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
      pvVar3 = memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_2 + 0x12e4),__n);
      memmove((void *)((int)pvVar3 + *(int *)(param_2 + 0x12e0)),param_3,local_158);
      RT_HMAC_SHA256(param_2 + 0x1aed,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n + sVar4,local_148
                     ,0x20);
    }
    iVar8 = AppendWSCTLV(0x1005,local_154,local_148,0);
    local_158 = iVar8 + local_158;
    *(size_t *)(param_2 + 0xadc) = local_158;
    local_154 = (void *)((int)local_154 + iVar8);
    memmove((void *)(param_2 + 0xae0),param_3,local_158);
    if (local_150 != 0) {
      os_free_mem();
    }
    *(undefined1 *)(param_2 + 0x1c53) = 0;
    sVar4 = local_158;
    if (2 < DebugLevel) {
      printk("BuildMessageM7 :\n");
      sVar4 = local_158;
    }
  }
  return sVar4;
}

