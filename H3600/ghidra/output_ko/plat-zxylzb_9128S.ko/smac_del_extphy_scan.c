// module: plat-zxylzb_9128S.ko
// function: smac_del_extphy_scan @ 0x1445c
// size: 8 bytes
//

void smac_del_extphy_scan(void)

{
  del_timer(extphy_timer);
  return;
}

