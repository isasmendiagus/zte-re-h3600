// module: tm.ko
// function: sipc_get_cpu_up_en @ 0x3027c
// size: 156 bytes
//

undefined4 sipc_get_cpu_up_en(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,&sipcRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sipc_get_cpu_up_en]output:enable = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sipc_get_cpu_up_en]read reg failed!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

