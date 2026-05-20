// module: plat-zxylzb_9128S.ko
// function: register_phy_int @ 0x1452c
// size: 140 bytes
//

undefined4 register_phy_int(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  char *local_28 [4];
  
  local_28[0] = "gphy0";
  local_28[1] = "gphy1";
  local_28[2] = "gphy2";
  local_28[3] = "gphy3";
  iVar3 = 0;
  puVar4 = (undefined4 *)g_phy_irq;
  puVar5 = &uni_phy;
  puVar6 = (undefined4 *)g_phy_hwirq;
  do {
    iVar2 = irq_to_desc(*puVar4);
    uVar1 = *puVar5;
    *puVar6 = *(undefined4 *)(iVar2 + 8);
    zx_mdio_write(uVar1,0x18,5);
    iVar2 = iVar3 + 1;
    request_threaded_irq(*puVar4,zx_phy_int,0,0,local_28[iVar3],iVar3);
    iVar3 = iVar2;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar2 != 4);
  return 0;
}

