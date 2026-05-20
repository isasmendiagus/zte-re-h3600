// module: mt7915.ko
// function: RT_HMAC_SHA384_VECTOR @ 0x1247e8
// size: 400 bytes
//

void RT_HMAC_SHA384_VECTOR
               (void *param_1,uint param_2,int param_3,undefined4 *param_4,int param_5,
               undefined4 *param_6,uint param_7)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  byte *pbVar6;
  undefined4 *puVar7;
  byte *pbVar9;
  byte **ppbVar10;
  undefined4 uVar11;
  byte *local_2a8;
  undefined4 local_2a4 [5];
  undefined4 local_290;
  undefined4 local_28c [5];
  undefined4 local_278 [11];
  byte bStack_249;
  byte local_248 [128];
  undefined1 auStack_1c8 [208];
  undefined1 auStack_f8 [212];
  undefined4 *puVar8;
  
  ppbVar10 = &local_2a8;
  __memzero(auStack_1c8,0xd0);
  __memzero(auStack_f8,0xd0);
  __memzero(local_248,0x80);
  if (param_2 < 0x81) {
    memcpy(local_248,param_1,param_2);
  }
  else {
    RT_SHA384(param_1,param_2,local_248);
  }
  pbVar6 = &bStack_249;
  pbVar9 = pbVar6;
  do {
    pbVar9 = pbVar9 + 1;
    *pbVar9 = *pbVar9 ^ 0x36;
  } while (pbVar9 != local_248 + 0x7f);
  RT_SHA384_Init(auStack_1c8);
  local_290 = 0x80;
  if (param_3 != 0) {
    puVar4 = (undefined4 *)(param_5 + -4);
    puVar1 = &local_290;
    puVar7 = param_4;
    do {
      puVar8 = puVar7 + 1;
      puVar4 = puVar4 + 1;
      uVar11 = *puVar4;
      ppbVar10 = ppbVar10 + 1;
      *ppbVar10 = (byte *)*puVar7;
      puVar1 = puVar1 + 1;
      *puVar1 = uVar11;
      puVar7 = puVar8;
    } while (puVar8 != param_4 + param_3);
  }
  local_2a8 = local_248;
  rt_sha384_vector(param_3 + 1U & 0xff,&local_2a8,&local_290,local_278);
  do {
    pbVar6 = pbVar6 + 1;
    *pbVar6 = *pbVar6 ^ 0x6a;
  } while (local_248 + 0x7f != pbVar6);
  RT_SHA384_Init(auStack_f8);
  RT_SHA384_Append(auStack_f8,local_248,0x80);
  RT_SHA384_Append(auStack_f8,local_278,0x30);
  RT_SHA384_End(auStack_f8,local_278);
  if (param_7 < 0x31) {
    memcpy(param_6,local_278,param_7);
    return;
  }
  puVar1 = local_278;
  do {
    uVar11 = *puVar1;
    uVar2 = puVar1[1];
    uVar3 = puVar1[2];
    uVar5 = puVar1[3];
    pbVar9 = (byte *)(puVar1 + 4);
    puVar1 = puVar1 + 4;
    *param_6 = uVar11;
    param_6[1] = uVar2;
    param_6[2] = uVar3;
    param_6[3] = uVar5;
    param_6 = param_6 + 4;
  } while (pbVar9 != local_248);
  return;
}

