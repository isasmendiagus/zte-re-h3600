// module: mt7915.ko
// function: MAP_InsertZteFakeRrmIE @ 0x1601ec
// size: 176 bytes
//

void MAP_InsertZteFakeRrmIE(undefined4 param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  int local_14;
  
  local_16 = 1;
  local_15 = 1;
  local_18 = 0xdd;
  local_17 = 7;
  MakeOutgoingFrame(param_3,&local_14,1,&local_18,1,&local_17,3,&ZTE_OUI,1,&ZTE_OUI_CAP_TYPE,1,
                    &MAP_ZTE_FAKE_RRM_SUBTYPE,1,&local_16,1,&local_15,0xffffffff);
  *param_4 = *param_4 + local_14;
  return;
}

