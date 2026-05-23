// module: plat-zxylzb_9128S.ko
// function: register_oam_int @ 0x130c8
// size: 44 bytes
//

void register_oam_int(undefined4 param_1)

{
  oam_isr = param_1;
  *(uint *)(npp_base + 4) = *(uint *)(npp_base + 4) & 0xfffbffff;
  return;
}

