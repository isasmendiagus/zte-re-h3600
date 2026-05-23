// module: plat-zxylzb_9128S.ko
// function: pp_gso_upload_enable @ 0x19928
// size: 248 bytes
//

void pp_gso_upload_enable(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if ((pp_gso_bp_cnt != 0) || (pp_disble_bp_pool != 0)) {
    pp_gso_upload_disable();
    printk("pp gso upload enable: release bp\n");
  }
  piVar3 = &pp_gso_bp_cnt;
  iVar2 = 0;
  do {
    iVar1 = pon_tm_bmu_alloc_bp();
    piVar3 = piVar3 + 1;
    *piVar3 = iVar1;
    if (iVar1 < 0) {
      printk("pp gso smb alloc bp failed\n");
      pp_gso_bp_cnt = iVar2;
      pp_gso_upload_disable();
      return;
    }
    iVar4 = u32_BP_SIZE * iVar1 + pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000;
    iVar1 = 0;
    if (u32_BP_SIZE + -0x10 != 0) {
      __memzero(iVar4,u32_BP_SIZE + -0x10);
      iVar1 = u32_BP_SIZE + -0x10;
    }
    iVar2 = iVar2 + 1;
    dma_cache_maint(iVar4,iVar1,1);
  } while (iVar2 != 0x400);
  pp_gso_bp_cnt = iVar2;
  pp_gso_bp_idx = 0;
  return;
}

