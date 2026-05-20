// module: tm.ko
// function: red_get_ind_acc_done @ 0x42710
// size: 176 bytes
//

undefined4 red_get_ind_acc_done(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(5,local_14,0,RedRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][red_get_ind_acc_done]output:Done = %d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7145,"red_get_ind_acc_done"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_red.c",0x1ed);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

