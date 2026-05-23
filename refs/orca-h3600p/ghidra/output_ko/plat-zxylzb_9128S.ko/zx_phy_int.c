// module: plat-zxylzb_9128S.ko
// function: zx_phy_int @ 0x13658
// size: 104 bytes
//

undefined4 zx_phy_int(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  *(undefined1 *)((int)&has_phy_int + (param_2 & 3)) = 1;
  iVar1 = (*(uint *)(g_phy_hwirq + (param_2 & 3) * 4) >> 5) * 4;
  piVar2 = (int *)(iVar1 + -0xfefee80);
  *piVar2 = 1 << (*(uint *)(g_phy_hwirq + (param_2 & 3) * 4) & 0x1f);
  iVar1 = _test_and_set_bit(0,0x21d50,piVar2,iVar1,param_4);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(phy_tasklet);
  }
  return 1;
}

