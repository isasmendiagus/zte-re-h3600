// module: plat-zxylzb_9128S.ko
// function: soft_insert_tx_1desc @ 0x191ac
// size: 64 bytes
//

void soft_insert_tx_1desc(undefined4 param_1,int param_2)

{
  dma_cache_maint(param_1,0x10,1);
  if (param_2 == 0) {
    *(undefined4 *)(tm_base + 0x10054) = 1;
    return;
  }
  *(undefined4 *)(tm_base + 0x10064) = 1;
  return;
}

