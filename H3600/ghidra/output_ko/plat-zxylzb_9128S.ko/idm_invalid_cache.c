// module: plat-zxylzb_9128S.ko
// function: idm_invalid_cache @ 0x15924
// size: 28 bytes
//

void idm_invalid_cache(uint param_1,int param_2)

{
  dma_cache_maint(param_1 & 0xffffffe0,
                  (param_2 + 0x1f + param_1 & 0xffffffe0) - (param_1 & 0xffffffe0),2);
  return;
}

