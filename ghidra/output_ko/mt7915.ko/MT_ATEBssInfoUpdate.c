// module: mt7915.ko
// function: MT_ATEBssInfoUpdate @ 0x27d72c
// size: 224 bytes
//

void MT_ATEBssInfoUpdate(undefined4 param_1,undefined4 param_2,undefined4 param_3,
                        undefined1 *param_4)

{
  undefined1 auStack_134 [4];
  undefined4 local_130;
  undefined1 local_128;
  undefined1 local_127;
  undefined1 auStack_126 [6];
  undefined2 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined1 local_114;
  undefined4 local_f8;
  
  if (2 < DebugLevel) {
    printk("%s: OwnMacIdx:%d BssIdx:%d Bssid:%02x:%02x:%02x:%02x:%02x:%02x\n","MT_ATEBssInfoUpdate",
           param_2,param_3,*param_4,param_4[1],param_4[2],param_4[3],param_4[4],param_4[5]);
  }
  __memzero(auStack_134,0x114);
  local_128 = (undefined1)param_2;
  local_127 = (undefined1)param_3;
  os_move_mem(auStack_126,param_4,6);
  local_120 = 0;
  local_118 = 0x10002;
  local_11c = 0x10000;
  local_114 = 1;
  local_130 = 2;
  local_f8 = 2;
  AsicBssInfoUpdate(param_1,auStack_134);
  return;
}

