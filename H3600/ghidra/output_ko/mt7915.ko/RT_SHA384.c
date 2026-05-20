// module: mt7915.ko
// function: RT_SHA384 @ 0x1265f0
// size: 76 bytes
//

void RT_SHA384(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_e0 [208];
  
  __memzero(auStack_e0,0xd0);
  RT_SHA384_Init(auStack_e0);
  RT_SHA384_Append(auStack_e0,param_1,param_2);
  RT_SHA384_End(auStack_e0,param_3);
  return;
}

