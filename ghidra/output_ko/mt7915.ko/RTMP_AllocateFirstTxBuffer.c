// module: mt7915.ko
// function: RTMP_AllocateFirstTxBuffer @ 0x25ff0c
// size: 28 bytes
//

void RTMP_AllocateFirstTxBuffer
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 *param_5)

{
  undefined4 uVar1;
  
  uVar1 = __kmalloc(param_3,0xd0);
  *param_5 = uVar1;
  return;
}

