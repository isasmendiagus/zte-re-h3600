// module: tm.ko
// function: sch_get_ind_acc_data @ 0x3d974
// size: 156 bytes
//

int sch_get_ind_acc_data(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0xf,local_14,param_2,&SchRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_ind_acc_data]output:data = %d\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x421);
  }
  return iVar1;
}

