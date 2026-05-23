// module: tm.ko
// function: sch_set_sw_age_pqid @ 0x3d618
// size: 132 bytes
//

undefined4
sch_set_sw_age_pqid(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_sw_age_pqid]input:pqid_msk = %d\n",param_1,param_3,g_tm_debug_level,param_4
          );
  }
  iVar1 = tmOnuRegWrite(0xb,param_1,0,&SchRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_sch.c",0x37d,g_tm_debug_level,param_4);
  return 0xffffffff;
}

