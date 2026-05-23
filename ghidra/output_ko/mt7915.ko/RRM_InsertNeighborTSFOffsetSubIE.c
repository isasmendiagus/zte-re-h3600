// module: mt7915.ko
// function: RRM_InsertNeighborTSFOffsetSubIE @ 0x21d03c
// size: 124 bytes
//

void RRM_InsertNeighborTSFOffsetSubIE
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined2 param_4)

{
  undefined2 local_1a [2];
  undefined1 local_16;
  undefined1 local_15;
  int local_14 [2];
  
  local_15 = 1;
  local_16 = 4;
  local_1a[0] = param_4;
  MakeOutgoingFrame(param_2,local_14,1,&local_15,1,&local_16,2,local_1a,2,&stack0x00000000,
                    0xffffffff);
  *param_3 = *param_3 + local_14[0];
  return;
}

