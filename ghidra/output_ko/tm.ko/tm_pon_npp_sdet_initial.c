// module: tm.ko
// function: tm_pon_npp_sdet_initial @ 0x4ebb4
// size: 104 bytes
//

uint tm_pon_npp_sdet_initial(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = 0;
  uVar4 = 0;
  do {
    uVar1 = sdet_set_maxframe_length(iVar3,0x3000);
    iVar3 = iVar3 + 1;
    uVar4 = uVar4 | uVar1;
  } while (iVar3 != 5);
  uVar1 = sdet_set_minframe_length(0xc);
  uVar2 = sdet_set_down_maxframe_length(0x3000);
  uVar2 = uVar1 | uVar4 | uVar2;
  if (uVar2 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x30f);
  }
  return uVar2;
}

