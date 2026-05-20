// module: mt7915.ko
// function: RT_HMAC_SHA256 @ 0x124390
// size: 352 bytes
//

void RT_HMAC_SHA256(void *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 *param_5,uint param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined4 local_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 local_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  byte local_140 [64];
  undefined1 auStack_100 [112];
  undefined1 auStack_90 [116];
  
  __memzero(auStack_100,0x70);
  __memzero(auStack_90,0x70);
  __memzero(local_140,0x40);
  if (param_2 < 0x41) {
    memcpy(local_140,param_1,param_2);
  }
  else {
    RT_SHA256(param_1,param_2,local_140);
  }
  pbVar1 = (byte *)((int)&uStack_144 + 3);
  pbVar2 = pbVar1;
  do {
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar2 ^ 0x36;
  } while (pbVar2 != local_140 + 0x3f);
  RT_SHA256_Init(auStack_100);
  RT_SHA256_Append(auStack_100,local_140,0x40);
  RT_SHA256_Append(auStack_100,param_3,param_4);
  RT_SHA256_End(auStack_100,&local_160);
  do {
    pbVar1 = pbVar1 + 1;
    *pbVar1 = *pbVar1 ^ 0x6a;
  } while (pbVar1 != local_140 + 0x3f);
  RT_SHA256_Init(auStack_90);
  RT_SHA256_Append(auStack_90,local_140,0x40);
  RT_SHA256_Append(auStack_90,&local_160,0x20);
  RT_SHA256_End(auStack_90,&local_160);
  if (param_6 < 0x21) {
    memcpy(param_5,&local_160,param_6);
    return;
  }
  *param_5 = local_160;
  param_5[1] = uStack_15c;
  param_5[2] = uStack_158;
  param_5[3] = uStack_154;
  param_5[4] = local_150;
  param_5[5] = uStack_14c;
  param_5[6] = uStack_148;
  param_5[7] = uStack_144;
  return;
}

