// module: tm.ko
// function: tm_tcont_sch_mode_get @ 0x4bcb8
// size: 84 bytes
//

undefined4 tm_tcont_sch_mode_get(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 0;
  iVar1 = uopc_get_tcont_sch_active_ena(&local_c);
  if (iVar1 == 0) {
    *param_1 = (uint)(local_c != 0);
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_que_sharp_ena_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

