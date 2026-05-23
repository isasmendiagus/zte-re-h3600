// module: plat-zxylzb_9128S.ko
// function: tm_get_tpid @ 0x10118
// size: 32 bytes
//

undefined4 tm_get_tpid(int param_1)

{
  return *(undefined4 *)(npp_base + param_1 * 4 + 0x9c);
}

