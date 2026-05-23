// module: mt7915.ko
// function: KDF_384 @ 0x1193c0
// size: 324 bytes
//

void KDF_384(undefined4 param_1,undefined4 param_2,void *param_3,size_t param_4,void *param_5,
            size_t param_6,int param_7,ushort param_8)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int unaff_r10;
  char *local_24;
  
  os_alloc_mem(0,&local_24,0x400);
  if (local_24 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("!!!KDF: no memory!!!\n");
    }
  }
  else {
    uVar4 = 1;
    __memzero(local_24,0x400);
    iVar1 = (uint)param_8 * 8;
    *local_24 = '\x01';
    local_24[1] = '\0';
    memmove(local_24 + 2,param_3,param_4);
    memmove(local_24 + param_4 + 2,param_5,param_6);
    iVar3 = param_4 + 2 + param_6;
    local_24[iVar3] = (char)iVar1;
    uVar2 = (iVar1 + 0x17fU) / 0x180;
    if (uVar2 != 0) {
      param_3 = (void *)0x30;
      unaff_r10 = param_7;
    }
    local_24[iVar3 + 1] = (char)((uint)iVar1 >> 8);
    if (uVar2 != 0) {
      do {
        RT_HMAC_SHA384(param_1,param_2,local_24,iVar3 + 2,unaff_r10,param_3);
        unaff_r10 = unaff_r10 + 0x30;
        uVar4 = uVar4 + 1 & 0xffff;
        *local_24 = *local_24 + '\x01';
      } while (uVar4 <= uVar2);
    }
    os_free_mem(local_24);
  }
  return;
}

