// module: plat-zxylzb_9128S.ko
// function: smac_sopc_mode_switch @ 0x13320
// size: 188 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void smac_sopc_mode_switch(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    (*_request_threaded_irq)(0x66665b0);
    if ((*(uint *)(dma_cfg_byteorder + npp_base + 4) & 1 << (param_1 + 5 & 0xff)) != 0) {
      *(uint *)(dma_cfg_byteorder + npp_base + 4) =
           *(uint *)(dma_cfg_byteorder + npp_base + 4) | 1 << (param_1 & 0xff);
      break;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(uint *)(npp_base + 0x19038) =
       *(uint *)(npp_base + 0x19038) & ~(1 << (param_1 + 0x10 & 0xff)) |
       (uint)(param_2 != 1) << (param_1 + 0x10 & 0xff);
                    /* WARNING: Could not recover jumptable at 0x000133c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_request_threaded_irq)(0x66665b0);
  return;
}

