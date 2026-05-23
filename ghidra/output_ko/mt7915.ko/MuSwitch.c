// module: mt7915.ko
// function: MuSwitch @ 0x22f834
// size: 32 bytes
//

void MuSwitch(undefined4 param_1,int param_2)

{
  if (param_2 != 0) {
    SetMuEnableProc(param_1,&_LC51);
    return;
  }
  SetMuEnableProc(param_1,&_LC50);
  return;
}

