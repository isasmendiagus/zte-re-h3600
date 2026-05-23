// module: mt7915.ko
// function: RRM_InsertRequestIE @ 0x21d228
// size: 108 bytes
//

void RRM_InsertRequestIE(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4,
                        undefined4 param_5)

{
  undefined1 local_16;
  undefined1 local_15;
  int local_14 [2];
  
  local_15 = (undefined1)param_4;
  local_16 = 10;
  MakeOutgoingFrame(param_2,local_14,1,&local_16,1,&local_15,param_4,param_5,0xffffffff);
  *param_3 = *param_3 + local_14[0];
  return;
}

