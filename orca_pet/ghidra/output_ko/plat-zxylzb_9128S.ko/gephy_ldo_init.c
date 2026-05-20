// module: plat-zxylzb_9128S.ko
// function: gephy_ldo_init @ 0x143e8
// size: 212 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 gephy_ldo_init(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined *in_r3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined *puVar8;
  
  puVar7 = &g_geLdoFlag;
  puVar4 = &uni_phy;
  puVar8 = in_r3;
  do {
    puVar5 = puVar4 + 1;
    zx_mdio_write(*puVar4,0x17,0x2448,in_r3,puVar8);
    uVar3 = _DAT_f0807010;
    uVar6 = _DAT_f080700c;
    iVar2 = _DAT_f0807004;
    iVar1 = _DAT_f0807000;
    zx_mdio_write(*puVar4,0x10,0xb640);
    if (iVar2 == 0 && iVar1 == 0) {
      zx_mdio_write(*puVar4,0x11,0x1f);
      *(undefined1 *)puVar7 = 0;
    }
    else {
      if (((uVar3 & 0xffff) == 0) && ((uVar6 & 0xfffe0000) == 0)) {
        uVar6 = uVar6 >> 0xf;
      }
      else {
        uVar6 = uVar6 & 0x8000;
      }
      if (uVar6 == 0) {
        zx_mdio_write(*puVar4,0x11,0x1f);
        *(undefined1 *)puVar7 = 0;
      }
      else {
        zx_mdio_write(*puVar4,0x11,0x1f);
        *(undefined1 *)puVar7 = 1;
      }
    }
    in_r3 = &DAT_00021d48;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar4 = puVar5;
  } while (puVar5 != &DAT_00021d48);
  return 0;
}

