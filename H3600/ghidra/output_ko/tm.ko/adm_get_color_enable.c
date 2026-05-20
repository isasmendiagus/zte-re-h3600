// module: tm.ko
// function: adm_get_color_enable @ 0x2a4d8
// size: 148 bytes
//

int adm_get_color_enable(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(2,local_14,0,AdmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_get_color_enable]output: colorEn = %d\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0xb6);
  }
  return iVar1;
}

