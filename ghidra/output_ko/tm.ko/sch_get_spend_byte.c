// module: tm.ko
// function: sch_get_spend_byte @ 0x3da90
// size: 152 bytes
//

int sch_get_spend_byte(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x10,local_14,0,&SchRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_spend_byte]output:spend_byte = %d\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x45e);
  }
  return iVar1;
}

