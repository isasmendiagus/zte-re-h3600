// module: mt7915.ko
// function: MAP_InsertMapZteIE @ 0x160124
// size: 196 bytes
//

void MAP_InsertMapZteIE(int param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  byte local_15;
  int local_14;
  
  local_18 = 0xdd;
  local_15 = (byte)*(int *)(param_1 + 0xa7cc00) & 7;
  if (-1 < *(int *)(param_1 + 0xa7cc00)) {
    local_15 = local_15 | 8;
  }
  local_17 = 7;
  local_16 = 1;
  MakeOutgoingFrame(param_3,&local_14,1,&local_18,1,&local_17,3,&ZTE_OUI,1,&ZTE_OUI_TYPE,1,
                    &MAP_ZTE_EXT,1,&local_16,1,&local_15,0xffffffff);
  *param_4 = *param_4 + local_14;
  return;
}

