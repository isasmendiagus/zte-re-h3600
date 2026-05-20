// module: mt7915.ko
// function: HcCrossChannelCheck @ 0xa9e60
// size: 56 bytes
//

void HcCrossChannelCheck(undefined4 param_1,int param_2,uint param_3)

{
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  uVar1 = param_3;
  if (0xe < param_3) {
    uVar1 = (uint)*(byte *)(param_2 + 0x1a);
  }
  if (0xe < uVar1) {
    return;
  }
  uVar1 = param_3;
  if (param_3 < 0xf) {
    uVar1 = (uint)*(byte *)(param_2 + 0x1a);
  }
  if (uVar1 < 0xf) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000a9e88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  if ((*(ushort *)(param_2 + 0x18) & 0xff) == 0) {
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  *(char *)(param_2 + 0x1a) = (char)param_3;
  HcAcquireRadioForWdev();
  return;
}

