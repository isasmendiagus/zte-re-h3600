// module: mt7915.ko
// function: KDF @ 0x119198
// size: 308 bytes
//

void * KDF(void *in,size_t inlen,void *out,size_t *outlen)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int unaff_r10;
  void *in_stack_00000000;
  size_t in_stack_00000004;
  int in_stack_00000008;
  ushort in_stack_0000000c;
  char *local_24;
  
  os_alloc_mem(0,&local_24,0x400);
  if (local_24 == (char *)0x0) {
    pvVar3 = (void *)0x0;
    if (-1 < DebugLevel) {
      pvVar3 = (void *)printk("!!!KDF: no memory!!!\n");
    }
  }
  else {
    uVar5 = 1;
    __memzero(local_24,0x400);
    iVar1 = (uint)in_stack_0000000c * 8;
    *local_24 = '\x01';
    local_24[1] = '\0';
    memmove(local_24 + 2,out,(size_t)outlen);
    memmove(local_24 + (int)outlen + 2,in_stack_00000000,in_stack_00000004);
    iVar4 = (int)outlen + 2 + in_stack_00000004;
    local_24[iVar4] = (char)iVar1;
    uVar2 = iVar1 + 0xffU >> 8;
    iVar6 = iVar1;
    if (uVar2 != 0) {
      iVar6 = 0x20;
      unaff_r10 = in_stack_00000008;
    }
    local_24[iVar4 + 1] = (char)((uint)iVar1 >> 8);
    if (uVar2 != 0) {
      do {
        RT_HMAC_SHA256(in,inlen,local_24,iVar4 + 2,unaff_r10,iVar6);
        unaff_r10 = unaff_r10 + 0x20;
        uVar5 = uVar5 + 1 & 0xffff;
        *local_24 = *local_24 + '\x01';
      } while (uVar5 <= uVar2);
    }
    pvVar3 = (void *)os_free_mem(local_24);
  }
  return pvVar3;
}

