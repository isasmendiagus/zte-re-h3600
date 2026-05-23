// module: mt7915.ko
// function: BuildMessageM4 @ 0x1f52c4
// size: 1440 bytes
//

size_t BuildMessageM4(int param_1,int param_2,void *param_3)

{
  size_t sVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;
  int iVar5;
  void *__src;
  size_t __n;
  size_t local_fc;
  void *local_f8;
  int local_f4;
  int local_f0;
  void *local_ec;
  undefined4 local_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined1 auStack_c8 [32];
  undefined1 auStack_a8 [132];
  
  local_ec = (void *)0x0;
  local_fc = 0;
  local_f4 = 0;
  local_f8 = param_3;
  os_alloc_mem(0,&local_ec,0x200);
  if (local_ec != (void *)0x0) {
    os_alloc_mem(0,&local_f4,0x90);
    if (local_f4 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: Allocate memory fail!!!\n","BuildMessageM4");
      }
    }
    else {
      iVar2 = AppendWSCTLV(0x104a,local_f8,param_2 + 0x70,0);
      local_e8 = CONCAT31(local_e8._1_3_,8);
      __src = (void *)(param_2 + 0x1bd0);
      iVar5 = param_2 + 0x1aed;
      local_f8 = (void *)((int)local_f8 + iVar2);
      local_fc = local_fc + iVar2;
      iVar2 = AppendWSCTLV(0x1022,local_f8,&local_e8,0);
      local_f8 = (void *)((int)local_f8 + iVar2);
      local_fc = local_fc + iVar2;
      iVar2 = AppendWSCTLV(0x101a,local_f8,param_2 + 0x1b40,0);
      local_f8 = (void *)((int)local_f8 + iVar2);
      local_fc = local_fc + iVar2;
      WscGenPSK1(param_1,param_2,&local_e8);
      *(undefined4 *)(param_2 + 0x1b70) = local_e8;
      *(undefined4 *)(param_2 + 0x1b7c) = uStack_dc;
      *(undefined4 *)(param_2 + 0x1b74) = uStack_e4;
      *(undefined4 *)(param_2 + 0x1b78) = uStack_e0;
      hex_dump(&_LC16,__src,0x10);
      hex_dump(&_LC17,(void *)(param_2 + 0x1be0),0x10);
      memmove(local_ec,__src,0x10);
      pvVar4 = local_ec;
      memmove((void *)((int)local_ec + 0x10),(undefined4 *)(param_2 + 0x1b70),0x10);
      memmove((void *)((int)pvVar4 + 0x20),(void *)(param_2 + 0x419),0xc0);
      memmove((void *)((int)pvVar4 + 0xe0),(void *)(param_2 + 0x4d9),0xc0);
      RT_HMAC_SHA256(iVar5,0x20,pvVar4,0x1a0,param_2 + 0x1bf0,0x20);
      iVar2 = AppendWSCTLV(0x103d,local_f8,param_2 + 0x1bf0,0);
      local_f8 = (void *)((int)local_f8 + iVar2);
      local_fc = local_fc + iVar2;
      WscGenPSK2(param_1,param_2,&local_e8);
      *(undefined4 *)(param_2 + 0x1b8c) = uStack_dc;
      *(undefined4 *)(param_2 + 0x1b80) = local_e8;
      *(undefined4 *)(param_2 + 0x1b84) = uStack_e4;
      *(undefined4 *)(param_2 + 0x1b88) = uStack_e0;
      memmove(local_ec,(void *)(param_2 + 0x1be0),0x10);
      pvVar4 = local_ec;
      memmove((void *)((int)local_ec + 0x10),(undefined4 *)(param_2 + 0x1b80),0x10);
      memmove((void *)((int)pvVar4 + 0x20),(void *)(param_2 + 0x419),0xc0);
      memmove((void *)((int)pvVar4 + 0xe0),(void *)(param_2 + 0x4d9),0xc0);
      RT_HMAC_SHA256(iVar5,0x20,pvVar4,0x1a0,&DAT_00001c10 + param_2,0x20);
      iVar2 = AppendWSCTLV(0x103e,local_f8,&DAT_00001c10 + param_2,0);
      local_f8 = (void *)((int)local_f8 + iVar2);
      local_fc = local_fc + iVar2;
      uVar3 = AppendWSCTLV(0x103f,auStack_a8,__src,0);
      RT_HMAC_SHA256(iVar5,0x20,auStack_a8,uVar3,&local_e8,0x20);
      if (uVar3 < 0x7c) {
        iVar2 = AppendWSCTLV(0x101e,auStack_a8 + uVar3,&local_e8,0);
        uVar3 = uVar3 + iVar2;
      }
      local_f0 = 0x80;
      AES_CBC_Encrypt(auStack_a8,uVar3,param_2 + 0x1b0d,0x10,local_f4,0x10,local_f4 + 0x10,&local_f0
                     );
      iVar2 = AppendWSCTLV(0x1018,local_f8,local_f4,local_f0 + 0x10U & 0xffff);
      local_f8 = (void *)((int)local_f8 + iVar2);
      local_fc = iVar2 + local_fc;
      if (((*(char *)(param_2 + 0x2b31) != '\0') &&
          (WscGenV2Msg(param_2,0,0,0,&local_f8,&local_fc), *(int *)(param_2 + 0x2b28) != 0)) &&
         (*(short *)(param_2 + 0x2b26) != 0)) {
        iVar2 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_f8);
        local_f8 = (void *)((int)local_f8 + iVar2);
        local_fc = iVar2 + local_fc;
      }
      sVar1 = local_fc;
      __n = *(size_t *)(param_2 + 0x12e0);
      if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
        pvVar4 = memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_2 + 0x12e4),__n);
        memmove((void *)((int)pvVar4 + *(int *)(param_2 + 0x12e0)),param_3,local_fc);
        RT_HMAC_SHA256(iVar5,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n + sVar1,auStack_c8,0x20);
      }
      iVar2 = AppendWSCTLV(0x1005,local_f8,auStack_c8,0);
      local_fc = iVar2 + local_fc;
      *(size_t *)(param_2 + 0xadc) = local_fc;
      local_f8 = (void *)((int)local_f8 + iVar2);
      memmove((void *)(param_2 + 0xae0),param_3,local_fc);
    }
    if (local_ec != (void *)0x0) {
      os_free_mem();
    }
    *(undefined1 *)(param_2 + 0x1c53) = 0;
    if (local_f4 != 0) {
      os_free_mem();
    }
    if (2 < DebugLevel) {
      printk("BuildMessageM4 :\n");
    }
  }
  return local_fc;
}

