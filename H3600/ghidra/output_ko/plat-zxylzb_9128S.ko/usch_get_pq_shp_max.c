// module: plat-zxylzb_9128S.ko
// function: usch_get_pq_shp_max @ 0x1ae00
// size: 96 bytes
//

int usch_get_pq_shp_max(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,3,param_2 == (uint *)0x0,param_4);
  if (iVar1 < 0) {
    DAT_0002e9b8 = DAT_0002e9b8 + 1;
  }
  else {
    *param_2 = *param_2 & 0x3fffff;
    iVar1 = 0;
  }
  return iVar1;
}

