// module: mt7915.ko
// function: RT_SHA1 @ 0x125ad0
// size: 76 bytes
//

void RT_SHA1(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_78 [104];
  
  __memzero(auStack_78,0x68);
  RT_SHA1_Init(auStack_78);
  RT_SHA1_Append(auStack_78,param_1,param_2);
  RT_SHA1_End(auStack_78,param_3);
  return;
}

