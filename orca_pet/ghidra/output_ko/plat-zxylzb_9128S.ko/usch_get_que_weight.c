// module: plat-zxylzb_9128S.ko
// function: usch_get_que_weight @ 0x1b290
// size: 96 bytes
//

int usch_get_que_weight(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,1,param_2 == (uint *)0x0,param_4);
  if (iVar1 < 0) {
    DAT_00030064 = DAT_00030064 + 1;
  }
  else {
    *param_2 = *param_2 & 0x3ffff;
    iVar1 = 0;
  }
  return iVar1;
}

