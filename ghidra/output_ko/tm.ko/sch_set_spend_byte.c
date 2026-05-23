// module: tm.ko
// function: sch_set_spend_byte @ 0x3da10
// size: 128 bytes
//

int sch_set_spend_byte(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_spend_byte]input:spend_byte = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(0x10,param_1,0,&SchRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x440,g_tm_debug_level,param_4);
  }
  return iVar1;
}

