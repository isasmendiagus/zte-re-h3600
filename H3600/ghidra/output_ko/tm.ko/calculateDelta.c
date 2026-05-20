// module: tm.ko
// function: calculateDelta @ 0x5ebec
// size: 20 bytes
//

uint calculateDelta(int param_1,int param_2)

{
  return (param_1 + param_2 & 0xffffU) + ((uint)(param_1 + param_2) >> 0x10) & 0xffff;
}

