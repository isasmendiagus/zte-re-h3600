// module: mt7915.ko
// function: greenap_get_capability @ 0x844a0
// size: 36 bytes
//

undefined1 greenap_get_capability(int param_1)

{
  undefined1 uVar1;
  
  if (param_1 == -0x36da94) {
    uVar1 = 0;
  }
  else {
    uVar1 = (&DAT_0036da94)[param_1];
  }
  return uVar1;
}

