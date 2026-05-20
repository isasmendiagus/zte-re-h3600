// module: plat-zxylzb_9128S.ko
// function: soft_insert_tx_multidesc @ 0x18e04
// size: 144 bytes
//

void soft_insert_tx_multidesc(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = param_1[1];
  uVar3 = param_1[2];
  uVar2 = 0x400 - (iVar1 - *param_1 >> 4);
  if (uVar2 < uVar3) {
    dma_cache_maint(iVar1,uVar2 * 0x10,1);
    dma_cache_maint(*param_1,(uVar3 - uVar2) * 0x10,1);
  }
  else {
    dma_cache_maint(iVar1,uVar3 << 4,1);
  }
  if (param_1[5] == 0) {
    *(uint *)(tm_base + 0x10054) = uVar3;
  }
  else {
    *(uint *)(tm_base + 0x10064) = uVar3;
  }
  param_1[6] = param_1[6] + uVar3;
  return;
}

