// module: tm.ko
// function: tm_tcont_sch_mode_set @ 0x4bc8c
// size: 44 bytes
//

undefined4 tm_tcont_sch_mode_set(int param_1)

{
  int iVar1;
  
  iVar1 = uopc_set_tcont_sch_active_ena(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tcont_sch_mode_set fail\n");
  return 0xffffffff;
}

