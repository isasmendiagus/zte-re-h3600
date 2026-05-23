// module: mt7915.ko
// function: GetEapolMsgType @ 0x1189e0
// size: 132 bytes
//

char * GetEapolMsgType(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 1) {
    return "Pairwise Message 1";
  }
  if (param_1 == 2) {
    return "Pairwise Message 2";
  }
  if (param_1 == 3) {
    return "Pairwise Message 3";
  }
  if (param_1 != 4) {
    if (param_1 != 5) {
      pcVar1 = "Group Message 2";
      if (param_1 != 6) {
        pcVar1 = "Invalid Message";
      }
      return pcVar1;
    }
    return "Group Message 1";
  }
  return "Pairwise Message 4";
}

