// module: mt7915.ko
// function: RRM_InsertRequestIE_11KV_API @ 0x21d294
// size: 112 bytes
//

void RRM_InsertRequestIE_11KV_API
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4,
               undefined1 param_5)

{
  undefined1 local_e;
  undefined1 local_d;
  int local_c;
  
  local_d = param_5;
  local_c = 0;
  local_e = 10;
  MakeOutgoingFrame(param_2,&local_c,1,&local_e,1,&local_d,param_5,param_4,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}

