// module: mt7915.ko
// function: MakeBeaconRepFrame @ 0x21cc48
// size: 180 bytes
//

void MakeBeaconRepFrame(undefined4 param_1,int param_2,int *param_3,undefined1 param_4,
                       undefined1 param_5,undefined1 param_6,undefined4 param_7,undefined1 param_8)

{
  undefined1 local_26;
  undefined1 local_25;
  int local_24 [2];
  
  InsertActField(param_1,param_2 + *param_3,param_3,param_5,param_6);
  InsertDialogToken(param_1,param_2 + *param_3,param_3,param_8);
  local_25 = 0x27;
  local_26 = param_4;
  MakeOutgoingFrame(param_2 + *param_3,local_24,1,&local_25,1,&local_26,3,param_7,0xffffffff);
  *param_3 = *param_3 + local_24[0];
  return;
}

