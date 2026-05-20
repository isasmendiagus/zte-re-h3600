// module: mt7915.ko
// function: HQA_TXBFProfileDataWriteAllExt @ 0x2712f4
// size: 228 bytes
//

undefined4 HQA_TXBFProfileDataWriteAllExt(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint local_24;
  uint local_20;
  char *local_1c;
  
  uVar3 = 0;
  local_24 = 0;
  local_20 = 0;
  os_alloc_mem(param_1,&local_1c,0x200);
  if (local_1c == (char *)0x0) {
    uVar3 = 3;
  }
  else {
    uVar1 = *(uint *)(param_3 + 0xc);
    uVar2 = *(uint *)(param_3 + 0x10);
    local_24 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
               uVar1 >> 0x18;
    local_20 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
               uVar2 >> 0x18;
    __memzero(local_1c,0x200);
    sprintf(local_1c,"%x:%x",local_20,local_24);
    if (local_1c == (char *)0x0) {
      uVar3 = 0;
    }
    else {
      os_free_mem();
    }
  }
  if (0 < DebugLevel) {
    printk("%s: bw:%x, profile_idx:%x\n","HQA_TXBFProfileDataWriteAllExt",local_24,local_20);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}

