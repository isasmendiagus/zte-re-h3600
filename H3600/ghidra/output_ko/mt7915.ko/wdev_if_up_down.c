// module: mt7915.ko
// function: wdev_if_up_down @ 0x14e520
// size: 12 bytes
//

void wdev_if_up_down(undefined4 param_1,int param_2,undefined1 param_3)

{
  if (param_2 != 0) {
    *(undefined1 *)(param_2 + 0x28) = param_3;
  }
  return;
}

