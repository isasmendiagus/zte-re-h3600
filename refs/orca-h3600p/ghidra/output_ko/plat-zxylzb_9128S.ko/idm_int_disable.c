// module: plat-zxylzb_9128S.ko
// function: idm_int_disable @ 0x15554
// size: 56 bytes
//

void idm_int_disable(uint param_1)

{
  idm_int_mask = *(uint *)(npp_base + 0x8024) | param_1;
  *(uint *)(npp_base + 0x8024) = idm_int_mask;
  return;
}

