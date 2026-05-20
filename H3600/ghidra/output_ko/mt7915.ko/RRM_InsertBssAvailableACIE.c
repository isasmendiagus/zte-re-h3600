// module: mt7915.ko
// function: RRM_InsertBssAvailableACIE @ 0x21d1b8
// size: 112 bytes
//

void RRM_InsertBssAvailableACIE(undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined1 local_10;
  undefined1 local_f;
  undefined2 local_e;
  int local_c;
  
  local_f = 2;
  local_10 = 0x43;
  local_e = 0;
  MakeOutgoingFrame(param_2,&local_c,1,&local_10,1,&local_f,2,&local_e,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}

