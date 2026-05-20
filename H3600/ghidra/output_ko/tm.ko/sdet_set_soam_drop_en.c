// module: tm.ko
// function: sdet_set_soam_drop_en @ 0x36ef0
// size: 244 bytes
//

undefined4 sdet_set_soam_drop_en(uint param_1,uint param_2)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  bool bVar4;
  bool bVar5;
  uint local_14;
  
  bVar5 = param_2 != 0;
  bVar4 = param_2 == 1;
  if (param_2 < 2) {
    bVar5 = 4 < param_1;
    bVar4 = param_1 == 5;
  }
  local_14 = 0;
  if (!bVar5 || bVar4) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_set_soam_drop_en]input:pro_pkt = %d, action = %d\n",param_1,param_2);
    }
    cVar1 = tmOnuRegRead(0x11,&local_14,0,&sdetgRegTable);
    cVar2 = tmOnuRegWrite(0x11,local_14 & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff),0,
                          &sdetgRegTable);
    uVar3 = 0;
    if (cVar1 != '\0' || cVar2 != '\0') {
      if (g_tm_debug_level == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        printk("[TM][sdet_set_soam_drop_en]write reg failed!\n");
        uVar3 = 0xffffffff;
      }
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 1;
  }
  else {
    printk("[TM][sdet_set_soam_drop_en]input invalid parameter!\n");
    uVar3 = 1;
  }
  return uVar3;
}

