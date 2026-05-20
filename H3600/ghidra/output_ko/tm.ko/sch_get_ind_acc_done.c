// module: tm.ko
// function: sch_get_ind_acc_done @ 0x3d838
// size: 172 bytes
//

undefined4 sch_get_ind_acc_done(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  local_c = 0;
  iVar1 = tmOnuRegRead(0xe,&local_c,0,&SchRegTable);
  if (iVar1 == 0) {
    if (local_c < 2) {
      *param_1 = local_c;
    }
    if (g_tm_debug_level < 7) {
      uVar2 = 0;
    }
    else {
      printk("[TM][sch_get_ind_acc_done]output:done = %d\n",*param_1);
      uVar2 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x3e4);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

