// module: mt7915.ko
// function: RTMPDisableDesiredHtInfo @ 0x138608
// size: 16 bytes
//

void RTMPDisableDesiredHtInfo(undefined4 param_1,int param_2)

{
  RTMPZeroMemory(param_2 + 0x891,0x1c);
  return;
}

