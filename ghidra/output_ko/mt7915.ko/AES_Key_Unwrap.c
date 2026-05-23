// module: mt7915.ko
// function: AES_Key_Unwrap @ 0x123e64
// size: 648 bytes
//

undefined4
AES_Key_Unwrap(undefined4 *param_1,uint param_2,undefined4 param_3,uint param_4,void *param_5,
              uint *param_6)

{
  uint uVar1;
  void *__dest;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  uint local_70;
  int local_6c;
  void *local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [12];
  
  local_54 = 0;
  if ((param_4 & 0xfffffff7) == 0x10 || param_4 == 0x20) {
    if ((7 < param_2) && ((param_2 & 7) == 0)) {
      param_2 = param_2 - 8;
      os_alloc_mem(0,&local_58,param_2);
      if (local_58 == (void *)0x0) {
        if (-1 < DebugLevel) {
          printk("AES_Key_Unwrap: allocate %zu bytes memory failure.\n",param_2);
          return 0xfffffffe;
        }
        return 0xfffffffe;
      }
      local_50 = *param_1;
      uStack_4c = param_1[1];
      uVar1 = param_2 >> 3;
      local_6c = 6;
      memmove(local_58,param_1 + 2,param_2);
      uVar3 = (uVar1 & 0xff) * 5;
      do {
        local_70 = uVar3 & 0xff;
        if (uVar1 - 1 != -1) {
          iVar5 = uVar1 - 1;
          iVar6 = (uVar1 + 0x1fffffff) * 8;
          do {
            uStack_4c = CONCAT13(uStack_4c._3_1_ ^ (char)uVar3 + '\x01' + (char)iVar5,
                                 (undefined3)uStack_4c);
            iVar5 = iVar5 + -1;
            local_38 = local_50;
            uStack_34 = uStack_4c;
            memmove(auStack_30,(void *)((int)local_58 + iVar6),8);
            local_54 = 0x10;
            RT_AES_Decrypt(&local_38,0x10,param_3,param_4,&local_48,&local_54);
            local_50 = local_48;
            uStack_4c = uStack_44;
            __dest = (void *)((int)local_58 + iVar6);
            iVar6 = iVar6 + -8;
            memmove(__dest,auStack_40,8);
          } while (iVar5 != -1);
        }
        uVar3 = local_70 - (uVar1 & 0xff);
        local_6c = local_6c + -1;
      } while (local_6c != 0);
      pcVar4 = &DAT_002986e3;
      pcVar2 = (char *)((int)&local_54 + 3);
      do {
        pcVar2 = pcVar2 + 1;
        pcVar4 = pcVar4 + 1;
        if (*pcVar2 != *pcVar4) {
          os_free_mem(local_58);
          return 0xffffffff;
        }
      } while (pcVar4 != (char *)((int)&DAT_002986e8 + 3));
      *param_6 = param_2;
      memmove(param_5,local_58,param_2);
      os_free_mem(local_58);
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s: CipherTextLength %d is invalid\n","AES_Key_Unwrap",param_2);
      return 0xffffffff;
    }
  }
  else if (-1 < DebugLevel) {
    printk("AES_Key_Unwrap: key length is %d bytes, it must be %d, %d, or %d bytes(128, 192, or 256 bits).\n"
           ,param_4,0x10,0x18,0x20);
    return 0xffffffff;
  }
  return 0xffffffff;
}

