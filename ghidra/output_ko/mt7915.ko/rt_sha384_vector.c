// module: mt7915.ko
// function: rt_sha384_vector @ 0x12663c
// size: 116 bytes
//

void rt_sha384_vector(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined1 auStack_e8 [208];
  
  __memzero(auStack_e8,0xd0);
  RT_SHA384_Init(auStack_e8);
  if (param_1 != 0) {
    puVar1 = (undefined4 *)(param_2 + -4);
    puVar2 = (undefined4 *)(param_3 + -4);
    do {
      puVar1 = puVar1 + 1;
      puVar2 = puVar2 + 1;
      RT_SHA384_Append(auStack_e8,*puVar1,*puVar2);
    } while (puVar1 != (undefined4 *)(param_2 + (param_1 - 1U & 0xff) * 4));
  }
  RT_SHA384_End(auStack_e8,param_4);
  return;
}

