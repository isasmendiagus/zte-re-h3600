// module: plat-zxylzb_9128S.ko
// function: net_invalid_cache @ 0x19418
// size: 28 bytes
//

void net_invalid_cache(uint param_1,int param_2)

{
  dma_cache_maint(param_1 & 0xffffffe0,
                  (param_2 + 0x1f + param_1 & 0xffffffe0) - (param_1 & 0xffffffe0),2);
  return;
}

