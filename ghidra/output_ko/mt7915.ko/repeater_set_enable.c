// module: mt7915.ko
// function: repeater_set_enable @ 0x83ae0
// size: 24 bytes
//

void repeater_set_enable(int param_1,undefined1 param_2,int param_3)

{
  (&DAT_0036790e)[param_1 + param_3] = param_2;
  return;
}

