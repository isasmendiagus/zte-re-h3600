// module: plat-zxylzb_9128S.ko
// function: dma_ram_get @ 0x18cb0
// size: 160 bytes
//

undefined4 dma_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x10018) & 1) != 0) {
      *(uint *)(tm_base + 0x10014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar2 = 0x14;
      do {
        if ((*(uint *)(tm_base + 0x10018) & 1) != 0) {
          *param_2 = *(undefined4 *)(tm_base + 0x1001c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("get dma ram %d/%d failed\n",param_3,param_1);
  return 0xfffffff5;
}

