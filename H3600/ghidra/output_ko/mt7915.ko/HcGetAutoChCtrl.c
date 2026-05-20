// module: mt7915.ko
// function: HcGetAutoChCtrl @ 0xa9b00
// size: 24 bytes
//

int HcGetAutoChCtrl(int param_1)

{
  return *(int *)(param_1 + 0xa797a0) + 0x1364;
}

