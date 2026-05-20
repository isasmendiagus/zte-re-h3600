// module: mt7915.ko
// function: greenap_init @ 0x84438
// size: 72 bytes
//

void greenap_init(int param_1)

{
  if (param_1 == -0x36da94) {
    return;
  }
  (&DAT_0036da94)[param_1] = 0;
  (&DAT_0036da95)[param_1] = 0;
  OS_SPIN_LOCK(&DAT_0036da9c + param_1);
  *(undefined4 *)(&DAT_0036da98 + param_1) = 0;
  OS_SPIN_UNLOCK(&DAT_0036da9c + param_1);
  return;
}

