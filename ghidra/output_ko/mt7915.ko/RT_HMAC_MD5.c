// module: mt7915.ko
// function: RT_HMAC_MD5 @ 0x124978
// size: 332 bytes
//

void RT_HMAC_MD5(void *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                undefined4 *param_5,uint param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined4 local_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  byte local_120 [64];
  undefined1 auStack_e0 [96];
  undefined1 auStack_80 [100];
  
  __memzero(auStack_e0,0x60);
  __memzero(auStack_80,0x60);
  __memzero(local_120,0x40);
  if (param_2 < 0x41) {
    memcpy(local_120,param_1,param_2);
  }
  else {
    RT_MD5(param_1,param_2,local_120);
  }
  pbVar1 = (byte *)((int)&uStack_124 + 3);
  pbVar2 = pbVar1;
  do {
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar2 ^ 0x36;
  } while (pbVar2 != local_120 + 0x3f);
  RT_MD5_Init(auStack_e0);
  RT_MD5_Append(auStack_e0,local_120,0x40);
  RT_MD5_Append(auStack_e0,param_3,param_4);
  RT_MD5_End(auStack_e0,&local_130);
  do {
    pbVar1 = pbVar1 + 1;
    *pbVar1 = *pbVar1 ^ 0x6a;
  } while (pbVar1 != local_120 + 0x3f);
  RT_MD5_Init(auStack_80);
  RT_MD5_Append(auStack_80,local_120,0x40);
  RT_MD5_Append(auStack_80,&local_130,0x10);
  RT_MD5_End(auStack_80,&local_130);
  if (param_6 < 0x11) {
    memcpy(param_5,&local_130,param_6);
    return;
  }
  *param_5 = local_130;
  param_5[1] = uStack_12c;
  param_5[2] = uStack_128;
  param_5[3] = uStack_124;
  return;
}

