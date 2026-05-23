// module: tm.ko
// function: calculatePortDelta @ 0x5ebd4
// size: 24 bytes
//

uint calculatePortDelta(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = param_1 + (~param_2 & 0xffff);
  return (uVar1 & 0xffff) + (uVar1 >> 0x10) & 0xffff;
}

