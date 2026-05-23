// module: mt7915.ko
// function: RT_HMAC_SHA384 @ 0x124684
// size: 356 bytes
//

void RT_HMAC_SHA384(void *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 *param_5,uint param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  undefined4 local_270 [11];
  byte bStack_241;
  byte local_240 [128];
  undefined1 auStack_1c0 [208];
  undefined1 auStack_f0 [212];
  
  puVar6 = local_270;
  __memzero(auStack_1c0,0xd0);
  __memzero(auStack_f0,0xd0);
  __memzero(local_240,0x80);
  if (param_2 < 0x81) {
    memcpy(local_240,param_1,param_2);
  }
  else {
    RT_SHA384(param_1,param_2,local_240);
  }
  pbVar5 = &bStack_241;
  pbVar7 = pbVar5;
  do {
    pbVar7 = pbVar7 + 1;
    *pbVar7 = *pbVar7 ^ 0x36;
  } while (pbVar7 != local_240 + 0x7f);
  RT_SHA384_Init(auStack_1c0);
  RT_SHA384_Append(auStack_1c0,local_240,0x80);
  RT_SHA384_Append(auStack_1c0,param_3,param_4);
  RT_SHA384_End(auStack_1c0,local_270);
  do {
    pbVar5 = pbVar5 + 1;
    *pbVar5 = *pbVar5 ^ 0x6a;
  } while (pbVar5 != local_240 + 0x7f);
  RT_SHA384_Init(auStack_f0);
  RT_SHA384_Append(auStack_f0,local_240,0x80);
  RT_SHA384_Append(auStack_f0,local_270,0x30);
  RT_SHA384_End(auStack_f0,local_270);
  if (0x30 < param_6) {
    do {
      uVar1 = *puVar6;
      uVar2 = puVar6[1];
      uVar3 = puVar6[2];
      uVar4 = puVar6[3];
      pbVar7 = (byte *)(puVar6 + 4);
      puVar6 = puVar6 + 4;
      *param_5 = uVar1;
      param_5[1] = uVar2;
      param_5[2] = uVar3;
      param_5[3] = uVar4;
      param_5 = param_5 + 4;
    } while (pbVar7 != local_240);
    return;
  }
  memcpy(param_5,local_270,param_6);
  return;
}

