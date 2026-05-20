// module: tm.ko
// function: tm_tcont_que_sch_sp_dwwr_mod_set @ 0x4bfbc
// size: 132 bytes
//

undefined4 tm_tcont_que_sch_sp_dwwr_mod_set(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_14;
  
  local_14 = 0;
  if ((param_3 == 0) && (sch_get_up_pq_sharp_bucket_cap(param_1,param_2,&local_14), local_14 == 0))
  {
    sch_set_up_pq_sharp_bucket_cap(param_1,param_2,200000);
  }
  iVar1 = sch_set_up_que_sp_dwrr_cfg(param_1,param_2,param_3 != 1);
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("tm_tcont_que_sch_sp_dwwr_mod_set fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

