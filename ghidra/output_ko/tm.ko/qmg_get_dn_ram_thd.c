// module: tm.ko
// function: qmg_get_dn_ram_thd @ 0x415ac
// size: 168 bytes
//

int qmg_get_dn_ram_thd(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,QmgRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][qmg_get_dn_ram_thd]output: thd_val = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_6938,"qmg_get_dn_ram_thd"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/tm_qmg.c",0xc6);
  }
  return iVar1;
}

