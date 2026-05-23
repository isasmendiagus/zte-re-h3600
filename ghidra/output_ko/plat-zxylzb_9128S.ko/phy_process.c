// module: plat-zxylzb_9128S.ko
// function: phy_process @ 0x142dc
// size: 152 bytes
//

void phy_process(void)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0;
  pcVar4 = (char *)&has_phy_int;
  do {
    if (*pcVar4 != '\0') {
      uVar1 = (&uni_phy)[uVar3];
      *pcVar4 = '\0';
      uVar2 = zx_mdio_read(uVar1,0x19);
      if ((uVar2 & 2) != 0) {
        *(undefined4 *)(g_SpeedChange + uVar3 * 4) = 1;
      }
      *(int *)((*(uint *)(g_phy_hwirq + uVar3 * 4) >> 5) * 4 + -0xfefef00) =
           1 << (*(uint *)(g_phy_hwirq + uVar3 * 4) & 0x1f);
      if (uVar3 != 4) {
        switch_phy_int_check_part_5(uVar3 & 0xff);
      }
    }
    uVar3 = uVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (uVar3 != 5);
  return;
}

