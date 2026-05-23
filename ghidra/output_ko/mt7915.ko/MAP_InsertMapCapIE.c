// module: mt7915.ko
// function: MAP_InsertMapCapIE @ 0x160070
// size: 180 bytes
//

void MAP_InsertMapCapIE(undefined4 param_1,int param_2,undefined4 param_3,int *param_4)

{
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  int local_14;
  
  local_15 = *(undefined1 *)(param_2 + 0x3f5d);
  local_16 = 1;
  local_18 = 0xdd;
  local_17 = 7;
  MakeOutgoingFrame(param_3,&local_14,1,&local_18,1,&local_17,3,&MAP_OUI,1,&MAP_OUI_TYPE,1,
                    &MAP_EXT_ATTRI,1,&local_16,1,&local_15,0xffffffff);
  *param_4 = *param_4 + local_14;
  return;
}

