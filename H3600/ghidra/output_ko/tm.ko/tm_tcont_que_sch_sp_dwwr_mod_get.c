// module: tm.ko
// function: tm_tcont_que_sch_sp_dwwr_mod_get @ 0x4be00
// size: 84 bytes
//

undefined4
tm_tcont_que_sch_sp_dwwr_mod_get(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 1;
  iVar1 = sch_get_up_que_sp_dwrr_cfg(param_1,param_2,&local_c);
  if (iVar1 == 0) {
    *(bool *)param_3 = local_c != 1;
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_que_sch_sp_dwwr_mod_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

