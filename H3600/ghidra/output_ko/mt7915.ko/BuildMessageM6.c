// module: mt7915.ko
// function: BuildMessageM6 @ 0x1f5bdc
// size: 892 bytes
//

size_t BuildMessageM6(int param_1,int param_2,void *param_3)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  size_t sVar4;
  size_t __n;
  size_t local_f8;
  void *local_f4;
  int local_f0;
  int local_ec;
  undefined1 local_e8 [32];
  undefined1 auStack_c8 [32];
  undefined1 auStack_a8 [132];
  
  local_f0 = 0;
  local_f8 = 0;
  local_f4 = param_3;
  os_alloc_mem(0,&local_f0,0x90);
  if (local_f0 == 0) {
    sVar4 = 0;
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","BuildMessageM6");
    }
  }
  else {
    iVar1 = AppendWSCTLV(0x104a,local_f4,param_2 + 0x70,0);
    local_e8[0] = 10;
    local_f4 = (void *)((int)local_f4 + iVar1);
    local_f8 = local_f8 + iVar1;
    iVar1 = AppendWSCTLV(0x1022,local_f4,local_e8,0);
    local_f4 = (void *)((int)local_f4 + iVar1);
    local_f8 = local_f8 + iVar1;
    iVar1 = AppendWSCTLV(0x101a,local_f4,param_2 + 0x1b40,0);
    local_f4 = (void *)((int)local_f4 + iVar1);
    local_f8 = local_f8 + iVar1;
    uVar2 = AppendWSCTLV(0x1040,auStack_a8,param_2 + 0x1be0,0);
    RT_HMAC_SHA256(param_2 + 0x1aed,0x20,auStack_a8,uVar2,local_e8,0x20);
    if (uVar2 < 0x7c) {
      iVar1 = AppendWSCTLV(0x101e,auStack_a8 + uVar2,local_e8,0);
      uVar2 = uVar2 + iVar1;
    }
    local_ec = 0x80;
    AES_CBC_Encrypt(auStack_a8,uVar2,param_2 + 0x1b0d,0x10,local_f0,0x10,local_f0 + 0x10,&local_ec);
    iVar1 = AppendWSCTLV(0x1018,local_f4,local_f0,local_ec + 0x10U & 0xffff);
    local_f4 = (void *)((int)local_f4 + iVar1);
    local_f8 = iVar1 + local_f8;
    if (((*(char *)(param_2 + 0x2b31) != '\0') &&
        (WscGenV2Msg(param_2,0,0,0,&local_f4,&local_f8), *(int *)(param_2 + 0x2b28) != 0)) &&
       (*(short *)(param_2 + 0x2b26) != 0)) {
      iVar1 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_f4);
      local_f4 = (void *)((int)local_f4 + iVar1);
      local_f8 = iVar1 + local_f8;
    }
    sVar4 = local_f8;
    __n = *(size_t *)(param_2 + 0x12e0);
    if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
      pvVar3 = memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_2 + 0x12e4),__n);
      memmove((void *)((int)pvVar3 + *(int *)(param_2 + 0x12e0)),param_3,local_f8);
      RT_HMAC_SHA256(param_2 + 0x1aed,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n + sVar4,
                     auStack_c8,0x20);
    }
    iVar1 = AppendWSCTLV(0x1005,local_f4,auStack_c8,0);
    sVar4 = iVar1 + local_f8;
    local_f4 = (void *)((int)local_f4 + iVar1);
    *(size_t *)(param_2 + 0xadc) = sVar4;
    local_f8 = sVar4;
    pvVar3 = memmove((void *)(param_2 + 0xae0),param_3,sVar4);
    memmove(pvVar3,param_3,sVar4);
    *(undefined1 *)(param_2 + 0x1c53) = 0;
    if (local_f0 != 0) {
      os_free_mem();
    }
    sVar4 = local_f8;
    if (2 < DebugLevel) {
      printk("BuildMessageM6 :\n");
      sVar4 = local_f8;
    }
  }
  return sVar4;
}

