// module: plat-zxylzb_9128S.ko
// function: pon_reset @ 0x1b284
// size: 96 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pon_reset(uint param_1)

{
  int iVar1;
  
  *(uint *)(pon_base + 8) = *(uint *)(pon_base + 8) & ~param_1;
  iVar1 = 100;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(uint *)(pon_base + 8) = *(uint *)(pon_base + 8) | param_1;
  return;
}

