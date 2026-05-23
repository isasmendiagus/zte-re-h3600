// module: plat-zxylzb_9128S.ko
// function: usch_set_que_weight @ 0x1b248
// size: 72 bytes
//

int usch_set_que_weight(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 0x3ffff,1,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  DAT_00030060 = DAT_00030060 + 1;
  return iVar1;
}

