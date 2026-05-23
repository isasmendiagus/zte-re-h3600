// module: mt7915.ko
// function: RTMPIoctlGetASSOCDATA @ 0xdd3a4
// size: 272 bytes
//

void RTMPIoctlGetASSOCDATA(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_18 [4];
  void *local_14;
  
  local_14 = (void *)0x0;
  if (param_1 != 0) {
    os_alloc_mem(0,&local_14,0x8ca4);
    if (local_14 == (void *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: Allocate memory fail!!!\n","RTMPIoctlGetASSOCDATA");
      }
    }
    else {
      __memzero(local_14,0x8ca4);
      memcpy(local_14,(void *)(param_1 + 0xa7dfb8),0x8ca4);
      *(undefined2 *)(param_2 + 0x14) = 0x8ca4;
      uVar1 = *(uint *)(param_2 + 0x10);
      uVar3 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
      if (uVar1 < 0xffff735c && uVar1 + 0x8ca4 <= uVar3) {
        uVar3 = 0;
      }
      if (((uVar3 != 0) || (iVar2 = __copy_to_user(uVar1,local_14,0x8ca4), iVar2 != 0)) &&
         (2 < DebugLevel)) {
        printk("%s: copy_to_user() fail\n","RTMPIoctlGetASSOCDATA");
      }
      if (local_14 != (void *)0x0) {
        os_free_mem();
      }
    }
  }
  return;
}

