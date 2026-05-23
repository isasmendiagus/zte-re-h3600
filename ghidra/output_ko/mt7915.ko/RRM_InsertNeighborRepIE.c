// module: mt7915.ko
// function: RRM_InsertNeighborRepIE @ 0x21cfd0
// size: 108 bytes
//

void RRM_InsertNeighborRepIE
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4,
               undefined4 param_5)

{
  undefined1 local_11 [4];
  undefined1 local_d;
  int local_c;
  
  local_d = 0x34;
  local_11[0] = param_4;
  MakeOutgoingFrame(param_2,&local_c,1,&local_d,1,local_11,0xd,param_5,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}

