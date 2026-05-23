// module: mt7915.ko
// function: RT_MD5 @ 0x125688
// size: 76 bytes
//

void RT_MD5(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_70 [96];
  
  __memzero(auStack_70,0x60);
  RT_MD5_Init(auStack_70);
  RT_MD5_Append(auStack_70,param_1,param_2);
  RT_MD5_End(auStack_70,param_3);
  return;
}

