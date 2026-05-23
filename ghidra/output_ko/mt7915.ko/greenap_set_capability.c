// module: mt7915.ko
// function: greenap_set_capability @ 0x84480
// size: 32 bytes
//

void greenap_set_capability(int param_1,undefined1 param_2)

{
  if (param_1 != -0x36da94) {
    (&DAT_0036da94)[param_1] = param_2;
  }
  return;
}

