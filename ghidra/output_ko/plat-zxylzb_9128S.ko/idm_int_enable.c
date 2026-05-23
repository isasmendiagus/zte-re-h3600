// module: plat-zxylzb_9128S.ko
// function: idm_int_enable @ 0x15978
// size: 56 bytes
//

void idm_int_enable(uint param_1)

{
  idm_int_mask = *(uint *)(npp_base + 0x8024) & ~param_1;
  *(uint *)(npp_base + 0x8024) = idm_int_mask;
  return;
}

