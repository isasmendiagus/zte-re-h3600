// module: mt7915.ko
// function: RT_SHA384_Init @ 0x125f9c
// size: 96 bytes
//

void RT_SHA384_Init(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  bool bVar6;
  
  puVar4 = &DAT_00298848;
  puVar5 = param_1;
  do {
    uVar1 = puVar4[1];
    uVar2 = puVar4[2];
    uVar3 = puVar4[3];
    bVar6 = puVar4 != (undefined4 *)&UNK_00298878;
    *puVar5 = *puVar4;
    puVar5[1] = uVar1;
    puVar5[2] = uVar2;
    puVar5[3] = uVar3;
    puVar4 = puVar4 + 4;
    puVar5 = puVar5 + 4;
  } while (bVar6);
  __memzero(param_1 + 0x12,0x80);
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x32] = 0;
  return;
}

