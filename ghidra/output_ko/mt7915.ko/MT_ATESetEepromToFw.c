// module: mt7915.ko
// function: MT_ATESetEepromToFw @ 0x27e41c
// size: 20 bytes
//

undefined4
MT_ATESetEepromToFw(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  MtCmdEfusBufferModeSet(param_1,2,param_3,param_4,param_4);
  return 0;
}

