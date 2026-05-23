// module: mt7915.ko
// function: HKDF_expand_sha384 @ 0x1192cc
// size: 244 bytes
//

void HKDF_expand_sha384(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                       int param_5,int param_6)

{
  void *__dest;
  size_t __n;
  int iVar1;
  char local_71;
  undefined1 *local_70;
  undefined4 local_6c;
  char *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 auStack_58 [52];
  
  local_68 = &local_71;
  local_64 = 0x30;
  local_71 = '\x01';
  local_5c = 1;
  iVar1 = 0;
  local_70 = auStack_58;
  local_6c = param_3;
  local_60 = param_4;
  RT_HMAC_SHA384_VECTOR(param_1,param_2,2,&local_6c,&local_60,auStack_58,0x30);
  while( true ) {
    __n = param_6 - iVar1;
    __dest = (void *)(param_5 + iVar1);
    if (0x2f < __n) {
      __n = 0x30;
    }
    iVar1 = iVar1 + __n;
    memcpy(__dest,auStack_58,__n);
    if (iVar1 == param_6) break;
    if (local_71 == -1) {
      os_zero_mem(param_5,param_6,3,&local_70);
      os_zero_mem(auStack_58,0x30);
      return;
    }
    local_71 = local_71 + '\x01';
    RT_HMAC_SHA384_VECTOR(param_1,param_2,3,&local_70,&local_64,auStack_58,0x30);
  }
  os_zero_mem(auStack_58,0x30,3,&local_70);
  return;
}

