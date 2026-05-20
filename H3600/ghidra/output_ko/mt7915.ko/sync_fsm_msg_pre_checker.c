// module: mt7915.ko
// function: sync_fsm_msg_pre_checker @ 0x10bd70
// size: 108 bytes
//

byte sync_fsm_msg_pre_checker
               (undefined4 param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *param_2;
  if ((bVar1 & 0xc) != 0) {
    return 0;
  }
  bVar2 = bVar1 >> 4;
  if (bVar2 == 5) {
    *param_3 = 4;
    *param_4 = 5;
    return 1;
  }
  if (bVar2 == 8) {
    *param_3 = 4;
    *param_4 = 6;
    return 1;
  }
  if (bVar2 != 4) {
    return bVar1 & 0xc;
  }
  *param_3 = 4;
  *param_4 = 4;
  return 1;
}

