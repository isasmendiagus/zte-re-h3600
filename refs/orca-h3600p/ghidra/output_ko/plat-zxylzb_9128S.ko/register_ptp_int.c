// module: plat-zxylzb_9128S.ko
// function: register_ptp_int @ 0x1309c
// size: 44 bytes
//

void register_ptp_int(undefined4 param_1)

{
  ptp_isr = param_1;
  *(uint *)(npp_base + 4) = *(uint *)(npp_base + 4) & 0xfffdffff;
  return;
}

