// module: plat-zxylzb_9128S.ko
// function: usch_set_que_wrr_pos @ 0x1b1a0
// size: 72 bytes
//

int usch_set_que_wrr_pos(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1f < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 7,0,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  usch_status = usch_status + 1;
  return iVar1;
}

