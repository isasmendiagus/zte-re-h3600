// module: mt7915.ko
// function: rt_sha256_vector @ 0x125f28
// size: 116 bytes
//

void rt_sha256_vector(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined1 auStack_88 [112];
  
  __memzero(auStack_88,0x70);
  RT_SHA256_Init(auStack_88);
  if (param_1 != 0) {
    puVar1 = (undefined4 *)(param_2 + -4);
    puVar2 = (undefined4 *)(param_3 + -4);
    do {
      puVar1 = puVar1 + 1;
      puVar2 = puVar2 + 1;
      RT_SHA256_Append(auStack_88,*puVar1,*puVar2);
    } while (puVar1 != (undefined4 *)(param_2 + (param_1 - 1U & 0xff) * 4));
  }
  RT_SHA256_End(auStack_88,param_4);
  return;
}

