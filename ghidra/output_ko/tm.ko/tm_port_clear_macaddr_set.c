// module: tm.ko
// function: tm_port_clear_macaddr_set @ 0x48cf4
// size: 176 bytes
//

undefined4 tm_port_clear_macaddr_set(uint param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int local_14 [2];
  
  cVar1 = sbrg_set_pt_macaddr_clr
                    ((param_1 << 0x1a) >> 0x1f | (param_1 & 0x1f) << 1 | param_1 & 0xc0,1);
  if (cVar1 == '\0') {
    iVar3 = 0;
    while (sbrg_get_ptclr_bit(local_14), local_14[0] != 1) {
      if (1 < g_tm_debug_level) {
        printk("[TM][tm_port_clear_macaddr_set]output:t_delay = %d\n",iVar3);
      }
      iVar3 = iVar3 + 1;
      if (iVar3 == 0x400) {
        return 0xffffffff;
      }
    }
    uVar2 = 0;
  }
  else {
    printk("tm_port_clear_macaddr_set fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

