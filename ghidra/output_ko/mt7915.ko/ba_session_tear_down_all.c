// module: mt7915.ko
// function: ba_session_tear_down_all @ 0xa6df4
// size: 76 bytes
//

void ba_session_tear_down_all
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  do {
    uVar2 = uVar1 & 0xff;
    uVar1 = uVar1 + 1;
    ba_ori_session_tear_down(param_1,param_2,uVar2,0,param_4);
    ba_rec_session_tear_down(param_1,param_2,uVar2,0);
  } while (uVar1 != 8);
  return;
}

