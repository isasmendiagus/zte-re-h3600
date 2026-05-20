// module: mt7915.ko
// function: RtmpAllocDescBuf @ 0x25fe64
// size: 104 bytes
//

void RtmpAllocDescBuf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 *param_5,undefined4 *param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 local_c;
  
  local_c = *param_6;
  if ((param_1 == 0) || (puVar2 = *(undefined4 **)(param_1 + 0x10c), puVar2 == (undefined4 *)0x0)) {
    puVar2 = &arm_dma_ops;
  }
  uVar1 = (*(code *)*puVar2)(param_1,param_3,&local_c,0x80d0,0);
  *param_5 = uVar1;
  *param_6 = local_c;
  return;
}

