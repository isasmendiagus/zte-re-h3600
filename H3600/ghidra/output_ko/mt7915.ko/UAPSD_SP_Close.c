// module: mt7915.ko
// function: UAPSD_SP_Close @ 0x1ddb84
// size: 24 bytes
//

void UAPSD_SP_Close(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  if (*(char *)(param_2 + 0xaf8) != '\x01') {
    return;
  }
  FUN_001dda04();
  return;
}

