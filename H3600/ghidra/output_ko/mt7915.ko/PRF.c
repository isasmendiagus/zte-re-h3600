// module: mt7915.ko
// function: PRF @ 0x119084
// size: 276 bytes
//

void PRF(undefined4 param_1,undefined4 param_2,void *param_3,size_t param_4,void *param_5,
        size_t param_6,int param_7,int param_8)

{
  void *extraout_r1;
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *local_24;
  
  os_alloc_mem(0,&local_24,0x400);
  if (local_24 == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("!!!PRF: no memory!!!\n");
    }
  }
  else {
    memmove(local_24,param_3,param_4);
    *(undefined1 *)((int)local_24 + param_4) = 0;
    iVar4 = param_4 + 1 + param_6;
    memmove((void *)((int)local_24 + param_4 + 1),param_5,param_6);
    iVar2 = (param_8 + 0x13) * 0x66666667;
    *(undefined1 *)((int)local_24 + iVar4) = 0;
    iVar3 = (param_8 + 0x13) / 0x14;
    pvVar1 = local_24;
    if (0 < iVar3) {
      iVar3 = param_7 + iVar3 * 0x14;
      do {
        RT_HMAC_SHA1(param_1,param_2,local_24,iVar4 + 1,param_7,0x14);
        param_7 = param_7 + 0x14;
        iVar2 = *(byte *)((int)local_24 + iVar4) + 1;
        *(char *)((int)local_24 + iVar4) = (char)iVar2;
        pvVar1 = extraout_r1;
      } while (param_7 != iVar3);
    }
    os_free_mem(local_24,pvVar1,iVar2);
  }
  return;
}

