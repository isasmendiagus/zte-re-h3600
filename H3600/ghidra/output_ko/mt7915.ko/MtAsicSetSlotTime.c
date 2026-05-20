// module: mt7915.ko
// function: MtAsicSetSlotTime @ 0x199a18
// size: 44 bytes
//

void MtAsicSetSlotTime(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4)

{
  MtCmdSlotTimeSet(param_1,param_2,param_3,2,0x3c,param_4);
  return;
}

