// module: tm.ko
// function: zte_api_sw_port_clear_port_count @ 0x62084
// size: 136 bytes
//

undefined4 zte_api_sw_port_clear_port_count(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar2 = 0;
  do {
    uVar1 = smac_set_cnt_rst(iVar3,1);
    iVar3 = iVar3 + 1;
    uVar2 = uVar2 | uVar1;
  } while (iVar3 != 5);
  if (uVar2 != 0) {
    printk("set smac clear enable failed\n");
    return 0xffffffff;
  }
  uVar2 = 0;
  iVar3 = 0;
  do {
    uVar1 = smac_set_cnt_rst(iVar3,0);
    iVar3 = iVar3 + 1;
    uVar2 = uVar2 | uVar1;
  } while (iVar3 != 5);
  if (uVar2 != 0) {
    printk("set smac clear disable failed\n");
    return 0xffffffff;
  }
  return 0;
}

