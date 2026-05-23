// module: mt7915.ko
// function: RtmpEepromGetDefault @ 0x1276ec
// size: 112 bytes
//

undefined4 RtmpEepromGetDefault(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x286280) == 4) {
    uVar1 = 2;
  }
  else {
    if ("Set_IRR_TTGOnOff"[param_1 + 1] == '\0') {
      uVar1 = 3;
    }
    else {
      uVar1 = 1;
    }
    if (*(int *)(param_1 + 0x286280) == 6) {
      uVar1 = 4;
    }
  }
  if (0 < DebugLevel) {
    printk("%s::e2p_dafault=%d\n","RtmpEepromGetDefault",uVar1);
  }
  return uVar1;
}

