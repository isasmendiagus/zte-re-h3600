// module: mt7915.ko
// function: _AndesUnlinkCmdMsg @ 0x1a47a8
// size: 56 bytes
//

void _AndesUnlinkCmdMsg(int param_1)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x48) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x48) + 4) = *(undefined4 *)(param_1 + 0x4c);
    }
    if (*(undefined4 **)(param_1 + 0x4c) != (undefined4 *)0x0) {
      **(undefined4 **)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x48);
    }
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    return;
  }
  return;
}

