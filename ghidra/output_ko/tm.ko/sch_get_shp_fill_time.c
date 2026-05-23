// module: tm.ko
// function: sch_get_shp_fill_time @ 0x3dc1c
// size: 172 bytes
//

int sch_get_shp_fill_time(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x11,local_14,0,&SchRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_shp_fill_time]output:fillTime = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7328,"sch_get_shp_fill_time"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x4a9);
  }
  return iVar1;
}

