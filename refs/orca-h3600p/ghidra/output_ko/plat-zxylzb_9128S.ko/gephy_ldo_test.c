// module: plat-zxylzb_9128S.ko
// function: gephy_ldo_test @ 0x13320
// size: 204 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
gephy_ldo_test(undefined2 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  uint uVar4;
  uint extraout_r3;
  undefined1 *puVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar4 = _DAT_f0807004 | _DAT_f0807000;
  if (uVar4 != 0) {
    uVar8 = _DAT_f0807010 & 0xffff;
    uVar1 = _DAT_f080700c & 0xfffe0000;
    uVar2 = _DAT_f080700c >> 0xf;
    uVar7 = _DAT_f080700c & 0x8000;
    puVar5 = &uni_phy;
    do {
      while ((uVar8 == 0 && (uVar1 == 0))) {
        if (uVar2 == 0) goto LAB_00013384;
        uVar3 = *puVar5;
LAB_000133b4:
        gephy_flag = 0;
        zx_mdio_write(uVar3,0x10,0xb640,uVar4,param_4);
        puVar6 = puVar5 + 1;
        zx_mdio_write(*puVar5,0x11,param_1);
        uVar4 = extraout_r3;
        puVar5 = puVar6;
        if (puVar6 == &DAT_00021d48) {
          return 0;
        }
      }
      if (uVar7 != 0) {
        uVar3 = *puVar5;
        uVar4 = 0;
        goto LAB_000133b4;
      }
LAB_00013384:
      puVar5 = puVar5 + 1;
    } while (puVar5 != &DAT_00021d48);
  }
  return 0;
}

