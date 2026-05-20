// module: plat-zxylzb_9128S.ko
// function: usch_set_pq_shp_fill @ 0x1ad10
// size: 72 bytes
//

int usch_set_pq_shp_fill(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 0x1fffff,2,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  DAT_0002e9b4 = DAT_0002e9b4 + 1;
  return iVar1;
}

