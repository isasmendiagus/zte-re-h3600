// module: tm.ko
// function: tm_pon_npp_sopc_initial @ 0x4ec94
// size: 136 bytes
//

uint tm_pon_npp_sopc_initial(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  uVar3 = 0;
  do {
    uVar1 = sopc_set_crc_pad_cfg(iVar2,0);
    iVar2 = iVar2 + 1;
    uVar3 = uVar3 | uVar1;
  } while (iVar2 != 5);
  if (uVar3 == 0) {
    uVar3 = opc_top_set_sp_rr_cfg(0);
    if (uVar3 == 0) {
      return 0;
    }
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x339);
    return uVar3;
  }
  printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x336);
  return uVar3;
}

