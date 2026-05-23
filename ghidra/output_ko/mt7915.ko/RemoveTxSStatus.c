// module: mt7915.ko
// function: RemoveTxSStatus @ 0x1e0294
// size: 112 bytes
//

undefined4
RemoveTxSStatus(int param_1,int param_2,undefined1 *param_3,undefined1 *param_4,undefined1 *param_5,
               undefined1 *param_6,undefined2 *param_7,undefined4 *param_8)

{
  param_1 = param_2 * 0xc + param_1;
  *param_3 = (&UNK_00296000)[param_1 + 0x5fa];
  *param_4 = (&UNK_00296000)[param_1 + 0x5fb];
  *param_5 = (&UNK_00296000)[param_1 + 0x5fc];
  *param_6 = (&UNK_00296000)[param_1 + 0x5fd];
  *param_7 = *(undefined2 *)(&UNK_00296000 + param_1 + 0x5fe);
  *param_8 = *(undefined4 *)(&UNK_00296000 + param_1 + 0x600);
  (&UNK_00296000)[param_1 + 0x5f9] = 0;
  return 0;
}

