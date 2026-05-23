// module: mt7915.ko
// function: RRM_InsertBssACDelayIE @ 0x21d13c
// size: 124 bytes
//

void RRM_InsertBssACDelayIE(undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined1 local_12;
  undefined1 local_11;
  int local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  
  local_11 = 4;
  local_c = 0xff;
  local_b = 0xff;
  local_a = 0xff;
  local_9 = 0xff;
  local_12 = 0x44;
  MakeOutgoingFrame(param_2,&local_10,1,&local_12,1,&local_11,4,&local_c,0xffffffff);
  *param_3 = *param_3 + local_10;
  return;
}

