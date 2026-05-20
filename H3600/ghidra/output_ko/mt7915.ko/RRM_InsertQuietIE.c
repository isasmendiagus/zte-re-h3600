// module: mt7915.ko
// function: RRM_InsertQuietIE @ 0x21d0b8
// size: 132 bytes
//

void RRM_InsertQuietIE(undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4,
                      undefined1 param_5,byte param_6,byte param_7)

{
  undefined1 local_1e;
  undefined1 local_1d;
  int local_1c;
  undefined1 local_16;
  undefined1 local_15;
  ushort local_14;
  ushort local_12;
  
  local_15 = param_5;
  local_14 = (ushort)param_6;
  local_12 = (ushort)param_7;
  local_1d = 6;
  local_1e = 0x28;
  local_16 = param_4;
  MakeOutgoingFrame(param_2,&local_1c,1,&local_1e,1,&local_1d,6,&local_16,0xffffffff);
  *param_3 = *param_3 + local_1c;
  return;
}

