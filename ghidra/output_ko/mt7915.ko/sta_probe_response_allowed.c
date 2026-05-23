// module: mt7915.ko
// function: sta_probe_response_allowed @ 0x76f24
// size: 128 bytes
//

bool sta_probe_response_allowed(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = GetStaCfgByWdev();
  if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
    return false;
  }
  if (*(byte *)(param_3 + 0x26) != 0) {
    if ((uint)*(byte *)(iVar1 + 0x212426) != (uint)*(byte *)(param_3 + 0x26)) {
      return false;
    }
    iVar1 = memcmp((void *)(param_3 + 6),(void *)(iVar1 + 0x212406),
                   (uint)*(byte *)(iVar1 + 0x212426));
    return iVar1 == 0;
  }
  return true;
}

