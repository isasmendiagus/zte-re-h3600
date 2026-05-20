// module: tm.ko
// function: tm_tcont_sec_sch_sp_dwwr_mod_set @ 0x546f4
// size: 44 bytes
//

undefined4
tm_tcont_sec_sch_sp_dwwr_mod_set
          (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = sch_set_secsch_sp_dwrr_cfg(param_1,param_2,param_3 != 1,param_4,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tcont_que_sch_sp_dwwr_mod_set fail\n");
  return 0xffffffff;
}

