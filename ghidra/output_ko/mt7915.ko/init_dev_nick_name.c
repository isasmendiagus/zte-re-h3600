// module: mt7915.ko
// function: init_dev_nick_name @ 0x176e0c
// size: 60 bytes
//

void init_dev_nick_name(int param_1)

{
  *(undefined4 *)(param_1 + 0x794abb) = 0x3937746d;
  *(undefined4 *)(param_1 + 0x794abf) = 0x735f3531;
  *(undefined2 *)(param_1 + 0x794ac3) = 0x6174;
  *(undefined1 *)(param_1 + 0x794ac5) = 0;
  return;
}

