// module: tm.ko
// function: tm_pon_npp_uopc_initial @ 0x4ec5c
// size: 56 bytes
//

int tm_pon_npp_uopc_initial(void)

{
  int iVar1;
  
  iVar1 = uopc_set_tcont_num(4);
  if (iVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x328);
  }
  return iVar1;
}

