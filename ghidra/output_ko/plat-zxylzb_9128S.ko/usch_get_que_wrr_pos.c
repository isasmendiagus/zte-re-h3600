// module: plat-zxylzb_9128S.ko
// function: usch_get_que_wrr_pos @ 0x1ac08
// size: 96 bytes
//

int usch_get_que_wrr_pos(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1f < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,0,param_4,param_4);
  if (iVar1 < 0) {
    usch_status = usch_status + 1;
  }
  else {
    *param_2 = *param_2 & 7;
    iVar1 = 0;
  }
  return iVar1;
}

