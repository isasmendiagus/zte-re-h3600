// module: mt7915.ko
// function: RT_HMAC_SHA256_VECTOR @ 0x1244f0
// size: 404 bytes
//

void RT_HMAC_SHA256_VECTOR
               (void *param_1,uint param_2,int param_3,undefined4 *param_4,int param_5,
               undefined4 *param_6,uint param_7)

{
  undefined4 *puVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  byte *pbVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  byte **ppbVar8;
  byte *local_198;
  undefined4 local_194 [5];
  undefined4 local_180;
  undefined4 local_17c [5];
  undefined4 local_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 local_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  byte local_148 [64];
  undefined1 auStack_108 [112];
  undefined1 auStack_98 [116];
  undefined4 *puVar4;
  
  ppbVar8 = &local_198;
  __memzero(auStack_108,0x70);
  __memzero(auStack_98,0x70);
  __memzero(local_148,0x40);
  if (param_2 < 0x41) {
    memcpy(local_148,param_1,param_2);
  }
  else {
    RT_SHA256(param_1,param_2,local_148);
  }
  pbVar5 = (byte *)((int)&uStack_14c + 3);
  pbVar2 = pbVar5;
  do {
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar2 ^ 0x36;
  } while (pbVar2 != local_148 + 0x3f);
  RT_SHA256_Init(auStack_108);
  local_180 = 0x40;
  if (param_3 != 0) {
    puVar7 = (undefined4 *)(param_5 + -4);
    puVar1 = &local_180;
    puVar3 = param_4;
    do {
      puVar4 = puVar3 + 1;
      puVar7 = puVar7 + 1;
      uVar6 = *puVar7;
      ppbVar8 = ppbVar8 + 1;
      *ppbVar8 = (byte *)*puVar3;
      puVar1 = puVar1 + 1;
      *puVar1 = uVar6;
      puVar3 = puVar4;
    } while (puVar4 != param_4 + param_3);
  }
  local_198 = local_148;
  rt_sha256_vector(param_3 + 1U & 0xff,&local_198,&local_180,&local_168);
  do {
    pbVar5 = pbVar5 + 1;
    *pbVar5 = *pbVar5 ^ 0x6a;
  } while (local_148 + 0x3f != pbVar5);
  RT_SHA256_Init(auStack_98);
  RT_SHA256_Append(auStack_98,local_148,0x40);
  RT_SHA256_Append(auStack_98,&local_168,0x20);
  RT_SHA256_End(auStack_98,&local_168);
  if (param_7 < 0x21) {
    memcpy(param_6,&local_168,param_7);
    return;
  }
  *param_6 = local_168;
  param_6[1] = uStack_164;
  param_6[2] = uStack_160;
  param_6[3] = uStack_15c;
  param_6[4] = local_158;
  param_6[5] = uStack_154;
  param_6[6] = uStack_150;
  param_6[7] = uStack_14c;
  return;
}

