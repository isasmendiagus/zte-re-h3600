// module: mt7915.ko
// function: PMF_ConstructBIPAad @ 0x219cf0
// size: 52 bytes
//

void PMF_ConstructBIPAad(undefined1 *param_1,undefined1 *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1] & 199;
  memmove(param_2 + 2,param_1 + 4,0x12);
  return;
}

