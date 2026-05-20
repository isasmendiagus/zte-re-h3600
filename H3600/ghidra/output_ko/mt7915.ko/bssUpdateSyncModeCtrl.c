// module: mt7915.ko
// function: bssUpdateSyncModeCtrl @ 0x1c2378
// size: 100 bytes
//

void bssUpdateSyncModeCtrl(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined2 local_18;
  undefined2 local_16;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (1 < *(uint *)(param_2 + 4)) {
    local_14 = CONCAT13(*(undefined1 *)(param_2 + 0x5a),CONCAT12(1,*(undefined2 *)(param_2 + 0x58)))
    ;
  }
  local_16 = 0x10;
  local_18 = 9;
  AndesAppendCmdMsg(param_3,&local_18,0x10);
  return;
}

