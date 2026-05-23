// module: mt7915.ko
// function: RT_HMAC_SHA1 @ 0x12423c
// size: 340 bytes
//

void RT_HMAC_SHA1(void *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 *param_5,uint param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined4 local_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 local_134;
  byte local_130 [64];
  undefined1 auStack_f0 [104];
  undefined1 auStack_88 [108];
  
  __memzero(auStack_f0,0x68);
  __memzero(auStack_88,0x68);
  __memzero(local_130,0x40);
  if (param_2 < 0x41) {
    memcpy(local_130,param_1,param_2);
  }
  else {
    RT_SHA1(param_1,param_2,local_130);
  }
  pbVar1 = (byte *)((int)&local_134 + 3);
  pbVar2 = pbVar1;
  do {
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar2 ^ 0x36;
  } while (pbVar2 != local_130 + 0x3f);
  RT_SHA1_Init(auStack_f0);
  RT_SHA1_Append(auStack_f0,local_130,0x40);
  RT_SHA1_Append(auStack_f0,param_3,param_4);
  RT_SHA1_End(auStack_f0,&local_144);
  do {
    pbVar1 = pbVar1 + 1;
    *pbVar1 = *pbVar1 ^ 0x6a;
  } while (pbVar1 != local_130 + 0x3f);
  RT_SHA1_Init(auStack_88);
  RT_SHA1_Append(auStack_88,local_130,0x40);
  RT_SHA1_Append(auStack_88,&local_144,0x14);
  RT_SHA1_End(auStack_88,&local_144);
  if (param_6 < 0x15) {
    memcpy(param_5,&local_144,param_6);
    return;
  }
  *param_5 = local_144;
  param_5[1] = uStack_140;
  param_5[2] = uStack_13c;
  param_5[4] = local_134;
  param_5[3] = uStack_138;
  return;
}

