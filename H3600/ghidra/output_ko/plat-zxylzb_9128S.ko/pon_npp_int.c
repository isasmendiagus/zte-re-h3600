// module: plat-zxylzb_9128S.ko
// function: pon_npp_int @ 0x130f4
// size: 120 bytes
//

undefined4 pon_npp_int(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *npp_base;
  uVar2 = npp_base[1];
  if (((uVar1 & ~uVar2 & 0x20000) != 0) && (ptp_isr != (code *)0x0)) {
    (*ptp_isr)(0,0);
  }
  if (((uVar1 & ~uVar2 & 0x40000) != 0) && (oam_isr != (code *)0x0)) {
    (*oam_isr)(0,0);
  }
  return 0;
}

