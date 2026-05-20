// module: mt7915.ko
// function: repeater_enable_by_any_band @ 0x83ac8
// size: 24 bytes
//

byte repeater_enable_by_any_band(int param_1)

{
  return (&DAT_0036790f)[param_1] | (&DAT_0036790e)[param_1];
}

