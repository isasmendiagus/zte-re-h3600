// module: mt7915.ko
// function: DfsGetBgndParameter @ 0x22ff3c
// size: 84 bytes
//

undefined1 DfsGetBgndParameter(int param_1,undefined4 param_2)

{
  switch(param_2) {
  default:
    return *(undefined1 *)(param_1 + 0x795130);
  case 1:
    return *(undefined1 *)(param_1 + 0x795131);
  case 2:
    return *(undefined1 *)(param_1 + 0x795134);
  case 3:
    return *(undefined1 *)(param_1 + 0x795135);
  case 4:
    return *(undefined1 *)(param_1 + 0x7953fb);
  case 5:
    return *(undefined1 *)(param_1 + 0x7953fc);
  case 6:
    return *(undefined1 *)(param_1 + 0x7953fd);
  case 7:
    return *(undefined1 *)(param_1 + 0x7953fe);
  }
}

