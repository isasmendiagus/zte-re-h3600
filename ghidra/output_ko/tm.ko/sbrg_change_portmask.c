// module: tm.ko
// function: sbrg_change_portmask @ 0x177a8
// size: 24 bytes
//

uint sbrg_change_portmask(uint param_1)

{
  return (param_1 << 0x1a) >> 0x1b | (param_1 & 1) << 5 | param_1 & 0xc0;
}

