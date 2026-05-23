// module: mt7915.ko
// function: sae_check_token @ 0x209700
// size: 120 bytes
//

bool sae_check_token(int param_1,void *param_2,int param_3)

{
  int iVar1;
  undefined1 auStack_30 [32];
  
  if (param_1 == 0) {
    return false;
  }
  if (param_3 != 0x20) {
    return false;
  }
  RT_HMAC_SHA256(*(int *)(param_1 + 0x180) + 0x1b910,6,param_1 + 0x166,6,auStack_30,0x20);
  iVar1 = memcmp(auStack_30,param_2,0x20);
  return iVar1 == 0;
}

