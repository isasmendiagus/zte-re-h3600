// module: mt7915.ko
// function: AES_Key_Wrap @ 0x123c48
// size: 536 bytes
//

undefined4
AES_Key_Wrap(void *param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 *param_5,
            int *param_6)

{
  uint uVar1;
  undefined4 uVar2;
  void *__dest;
  uint uVar3;
  int iVar4;
  bool bVar5;
  uint local_6c;
  int local_68;
  void *local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  byte bStack_41;
  undefined1 auStack_40 [8];
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [12];
  
  bVar5 = (param_4 & 0xfffffff7) == 0x10;
  local_54 = 0;
  if (bVar5 || param_4 == 0x20) {
    os_alloc_mem(!bVar5 && param_4 != 0x20,&local_58,param_2);
    if (local_58 != (void *)0x0) {
      uVar1 = param_2 >> 3;
      local_6c = 1;
      local_68 = 6;
      local_50 = 0xa6a6a6a6;
      uStack_4c = 0xa6a6a6a6;
      memmove(local_58,param_1,param_2);
      do {
        if (uVar1 != 0) {
          iVar4 = 0;
          uVar3 = local_6c;
          do {
            local_38 = local_50;
            uStack_34 = uStack_4c;
            memmove(auStack_30,(void *)((int)local_58 + iVar4),8);
            local_54 = 0x10;
            RT_AES_Encrypt(&local_38,0x10,param_3,param_4,&local_48,&local_54);
            local_50 = local_48;
            __dest = (void *)((int)local_58 + iVar4);
            iVar4 = iVar4 + 8;
            uStack_4c = CONCAT13(bStack_41 ^ (byte)uVar3,(int3)uStack_44);
            memmove(__dest,auStack_40,8);
            uVar3 = uVar3 + 1 & 0xff;
          } while (iVar4 != uVar1 << 3);
        }
        local_68 = local_68 + -1;
        local_6c = local_6c + (uVar1 & 0xff) & 0xff;
      } while (local_68 != 0);
      *param_6 = param_2 + 8;
      *param_5 = local_50;
      param_5[1] = uStack_4c;
      memmove(param_5 + 2,local_58,param_2);
      os_free_mem(local_58);
      return 0;
    }
    if (DebugLevel < 0) {
      uVar2 = 0xfffffffe;
    }
    else {
      printk("AES_Key_Wrap: allocate %zu bytes memory failure.\n",param_2);
      uVar2 = 0xfffffffe;
    }
  }
  else if (DebugLevel < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("AES_Key_Wrap: key length is %d bytes, it must be %d, %d, or %d bytes(128, 192, or 256 bits).\n"
           ,param_4,0x10,0x18,0x20);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

