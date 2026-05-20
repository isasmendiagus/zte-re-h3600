// module: tm.ko
// function: sch_set_ind_acc_data @ 0x3d8e4
// size: 144 bytes
//

int sch_set_ind_acc_data(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_ind_acc_data]input:data = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(0xf,param_1,param_2,&SchRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_sch.c",0x404);
  }
  return iVar1;
}

