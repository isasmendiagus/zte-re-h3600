// module: tm.ko
// function: tm_pon_npp_smac_initial @ 0x4eff0
// size: 80 bytes
//

int tm_pon_npp_smac_initial(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    iVar1 = smac_set_tsf_mode(iVar2);
    iVar2 = iVar3;
  } while (iVar3 != 5);
  if (iVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x3db);
  }
  return iVar1;
}

