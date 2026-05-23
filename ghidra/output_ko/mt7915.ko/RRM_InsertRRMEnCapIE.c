// module: mt7915.ko
// function: RRM_InsertRRMEnCapIE @ 0x21cfb0
// size: 32 bytes
//

void RRM_InsertRRMEnCapIE
               (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  if (*(int *)(param_2 + 0x14) != 2) {
    RRM_InsertAPRRMEnCapIE();
    return;
  }
  RRM_InsertSTARRMEnCapIE(param_1,param_3,param_4,param_5);
  return;
}

