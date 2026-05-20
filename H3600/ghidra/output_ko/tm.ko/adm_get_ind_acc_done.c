// module: tm.ko
// function: adm_get_ind_acc_done @ 0x2ac10
// size: 184 bytes
//

undefined4 adm_get_ind_acc_done(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  local_c = 0;
  iVar1 = tmOnuRegRead(6,&local_c,0,AdmRegTable);
  if (iVar1 == 0) {
    if (local_c < 2) {
      *param_1 = local_c;
    }
    if (g_tm_debug_level < 7) {
      uVar2 = 0;
    }
    else {
      printk("[TM][adm_get_ind_acc_done]output: Done = %d\n",local_c & 1);
      uVar2 = 0;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7136,"adm_get_ind_acc_done"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x21e);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

