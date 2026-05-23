// module: mt7915.ko
// function: Show_BndStrg_Info @ 0x9b8ac
// size: 88 bytes
//

undefined4 Show_BndStrg_Info(int param_1)

{
  if (*(undefined4 **)(&DAT_0036c93c + param_1) != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)(&DAT_0036c93c + param_1))(&DAT_0036b924 + param_1);
  }
  if (*(undefined4 **)(&DAT_0036d9d0 + param_1) != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)(&DAT_0036d9d0 + param_1))(&DAT_0036c9b8 + param_1);
  }
  return 1;
}

