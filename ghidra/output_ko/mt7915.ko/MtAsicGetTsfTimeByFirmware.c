// module: mt7915.ko
// function: MtAsicGetTsfTimeByFirmware @ 0x1999e0
// size: 56 bytes
//

undefined4
MtAsicGetTsfTimeByFirmware
          (undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 local_18;
  undefined4 local_14;
  
  MtCmdGetTsfTime(param_1,param_4,&local_18);
  *param_2 = local_14;
  *param_3 = local_18;
  return 1;
}

