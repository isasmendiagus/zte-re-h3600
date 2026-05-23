// module: tm.ko
// function: tm_pon_pp_reg_initial @ 0x4da50
// size: 316 bytes
//

uint tm_pon_pp_reg_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = pon_pp_set_mult_mode(0,0);
  uVar2 = pon_pp_set_mult_mode(0,1);
  uVar3 = pon_pp_set_jumb_len(0x800);
  uVar4 = pon_pp_set_pm_base_addr(pdt_mem_size + 0x40420000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  uVar5 = pon_pp_set_acl_base_addr(pdt_mem_size + 0x40020000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  uVar5 = uVar2 | uVar1 | uVar3 | uVar4 | uVar5;
  if (uVar5 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x159);
    return uVar5;
  }
  iVar7 = 1;
  iVar6 = 0;
  do {
    if (iVar6 == 3) {
      pon_pp_set_tpid(0x9200,3);
    }
    else if (iVar6 == 1) {
      pon_pp_set_tpid(0x9100,1);
    }
    else {
      uVar1 = pon_pp_set_tpid(0x8100,iVar6);
      if (iVar7 == 8) {
        if (uVar1 == 0) {
          return 0;
        }
        printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x182);
        return uVar1;
      }
    }
    while( true ) {
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + 1;
      if (iVar6 != 2) break;
      pon_pp_set_tpid(0x88a8,2);
    }
  } while( true );
}

