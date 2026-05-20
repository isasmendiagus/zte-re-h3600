// module: mt7915.ko
// function: HKDF_expand_sha256 @ 0x119504
// size: 244 bytes
//

void HKDF_expand_sha256(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                       int param_5,int param_6)

{
  void *__dest;
  size_t __n;
  int iVar1;
  char local_61;
  undefined1 *local_60;
  undefined4 local_5c;
  char *local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 auStack_48 [36];
  
  local_58 = &local_61;
  local_54 = 0x20;
  local_61 = '\x01';
  local_4c = 1;
  iVar1 = 0;
  local_60 = auStack_48;
  local_5c = param_3;
  local_50 = param_4;
  RT_HMAC_SHA256_VECTOR(param_1,param_2,2,&local_5c,&local_50,auStack_48,0x20);
  while( true ) {
    __n = param_6 - iVar1;
    __dest = (void *)(param_5 + iVar1);
    if (0x1f < __n) {
      __n = 0x20;
    }
    iVar1 = iVar1 + __n;
    memcpy(__dest,auStack_48,__n);
    if (iVar1 == param_6) break;
    if (local_61 == -1) {
      os_zero_mem(param_5,param_6,3,&local_60);
      os_zero_mem(auStack_48,0x20);
      return;
    }
    local_61 = local_61 + '\x01';
    RT_HMAC_SHA256_VECTOR(param_1,param_2,3,&local_60,&local_54,auStack_48,0x20);
  }
  os_zero_mem(auStack_48,0x20,3,&local_60);
  return;
}

