// module: mt7915.ko
// function: RT_SHA256 @ 0x125edc
// size: 76 bytes
//

void RT_SHA256(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_80 [112];
  
  __memzero(auStack_80,0x70);
  RT_SHA256_Init(auStack_80);
  RT_SHA256_Append(auStack_80,param_1,param_2);
  RT_SHA256_End(auStack_80,param_3);
  return;
}

