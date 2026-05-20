// module: mt7915.ko
// function: RTMPTkipAppend @ 0x1174d0
// size: 44 bytes
//

void RTMPTkipAppend(undefined4 param_1,undefined1 *param_2,int param_3)

{
  if (param_3 == 0) {
    return;
  }
  do {
    RTMPTkipAppendByte(param_1,*param_2);
    param_3 = param_3 + -1;
    param_2 = param_2 + 1;
  } while (param_3 != 0);
  return;
}

