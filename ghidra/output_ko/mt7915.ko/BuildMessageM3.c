// module: mt7915.ko
// function: BuildMessageM3 @ 0x1f4e60
// size: 1124 bytes
//

size_t BuildMessageM3(int param_1,int param_2,void *param_3)

{
  size_t sVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  size_t __n;
  size_t local_54;
  void *local_50;
  void *local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  
  local_4c = (void *)0x0;
  local_54 = 0;
  local_50 = param_3;
  os_alloc_mem(0,&local_4c,0x200);
  if (local_4c != (void *)0x0) {
    iVar2 = AppendWSCTLV(0x104a,local_50,param_2 + 0x70,0);
    local_48 = CONCAT31(local_48._1_3_,7);
    local_50 = (void *)((int)local_50 + iVar2);
    local_54 = local_54 + iVar2;
    iVar2 = AppendWSCTLV(0x1022,local_50,&local_48,0);
    local_50 = (void *)((int)local_50 + iVar2);
    local_54 = local_54 + iVar2;
    iVar2 = AppendWSCTLV(0x1039,local_50,param_2 + 0x1b50,0);
    local_50 = (void *)((int)local_50 + iVar2);
    local_54 = local_54 + iVar2;
    WscGenPSK1(param_1,param_2,&local_48);
    *(undefined4 *)(param_2 + 0x1b70) = local_48;
    *(undefined4 *)(param_2 + 0x1b7c) = uStack_3c;
    *(undefined4 *)(param_2 + 0x1b74) = uStack_44;
    *(undefined4 *)(param_2 + 0x1b78) = uStack_40;
    hex_dump(&_LC16,(void *)(param_2 + 0x1bd0),0x10);
    hex_dump(&_LC17,(void *)(param_2 + 0x1be0),0x10);
    memmove(local_4c,(void *)(param_2 + 0x1bd0),0x10);
    pvVar3 = local_4c;
    iVar4 = param_2 + 0x1aed;
    memmove((void *)((int)local_4c + 0x10),(undefined4 *)(param_2 + 0x1b70),0x10);
    memmove((void *)((int)pvVar3 + 0x20),(void *)(param_2 + 0x419),0xc0);
    memmove((void *)((int)pvVar3 + 0xe0),(void *)(param_2 + 0x4d9),0xc0);
    RT_HMAC_SHA256(iVar4,0x20,pvVar3,0x1a0,param_2 + 0x1b90,0x20);
    iVar2 = AppendWSCTLV(0x1014,local_50,param_2 + 0x1b90,0);
    local_50 = (void *)((int)local_50 + iVar2);
    local_54 = local_54 + iVar2;
    WscGenPSK2(param_1,param_2,&local_48);
    *(undefined4 *)(param_2 + 0x1b8c) = uStack_3c;
    *(undefined4 *)(param_2 + 0x1b80) = local_48;
    *(undefined4 *)(param_2 + 0x1b84) = uStack_44;
    *(undefined4 *)(param_2 + 0x1b88) = uStack_40;
    memmove(local_4c,(void *)(param_2 + 0x1be0),0x10);
    pvVar3 = local_4c;
    memmove((void *)((int)local_4c + 0x10),(undefined4 *)(param_2 + 0x1b80),0x10);
    memmove((void *)((int)pvVar3 + 0x20),(void *)(param_2 + 0x419),0xc0);
    memmove((void *)((int)pvVar3 + 0xe0),(void *)(param_2 + 0x4d9),0xc0);
    RT_HMAC_SHA256(iVar4,0x20,pvVar3,0x1a0,param_2 + 0x1bb0,0x20);
    iVar2 = AppendWSCTLV(0x1015,local_50,param_2 + 0x1bb0,0);
    local_50 = (void *)((int)local_50 + iVar2);
    local_54 = iVar2 + local_54;
    if (((*(char *)(param_2 + 0x2b31) != '\0') &&
        (WscGenV2Msg(param_2,0,0,0,&local_50,&local_54), *(int *)(param_2 + 0x2b28) != 0)) &&
       (*(short *)(param_2 + 0x2b26) != 0)) {
      iVar2 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_50);
      local_50 = (void *)((int)local_50 + iVar2);
      local_54 = iVar2 + local_54;
    }
    sVar1 = local_54;
    __n = *(size_t *)(param_2 + 0x12e0);
    if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
      pvVar3 = memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_2 + 0x12e4),__n);
      memmove((void *)((int)pvVar3 + *(int *)(param_2 + 0x12e0)),param_3,local_54);
      RT_HMAC_SHA256(iVar4,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n + sVar1,&local_48,0x20);
    }
    iVar2 = AppendWSCTLV(0x1005,local_50,&local_48,0);
    local_54 = iVar2 + local_54;
    *(size_t *)(param_2 + 0xadc) = local_54;
    local_50 = (void *)((int)local_50 + iVar2);
    memmove((void *)(param_2 + 0xae0),param_3,local_54);
    if (local_4c != (void *)0x0) {
      os_free_mem();
    }
    *(undefined1 *)(param_2 + 0x1c53) = 0;
    if (2 < DebugLevel) {
      printk("BuildMessageM3 :\n");
    }
  }
  return local_54;
}

