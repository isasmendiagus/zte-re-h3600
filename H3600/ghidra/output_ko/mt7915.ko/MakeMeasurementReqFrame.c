// module: mt7915.ko
// function: MakeMeasurementReqFrame @ 0x13edf8
// size: 292 bytes
//

void MakeMeasurementReqFrame
               (undefined4 param_1,int param_2,int *param_3,undefined1 param_4,char param_5,
               undefined1 param_6,undefined1 param_7,undefined1 param_8,undefined1 param_9,
               undefined2 param_10)

{
  int iVar1;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined2 local_36;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  int local_30;
  int local_2c [2];
  
  local_36 = param_10;
  InsertActField(param_1,param_2 + *param_3,param_3,param_5,param_6);
  local_39 = param_7;
  MakeOutgoingFrame(param_2 + *param_3,local_2c,1,&local_39,0xffffffff);
  iVar1 = *param_3;
  *param_3 = iVar1 + local_2c[0];
  if (param_5 == '\x05') {
    MakeOutgoingFrame(param_2 + iVar1 + local_2c[0],&local_30,2,&local_36,0xffffffff);
    *param_3 = *param_3 + local_30;
  }
  __memzero(&local_33,3);
  local_33 = param_7;
  local_37 = 0x26;
  local_32 = param_8;
  local_31 = param_9;
  local_38 = param_4;
  MakeOutgoingFrame(param_2 + *param_3,local_2c,1,&local_37,1,&local_38,3,&local_33,0xffffffff);
  *param_3 = *param_3 + local_2c[0];
  return;
}

