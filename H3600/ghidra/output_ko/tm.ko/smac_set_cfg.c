// module: tm.ko
// function: smac_set_cfg @ 0x30318
// size: 580 bytes
//

int smac_set_cfg(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  if (((((((((param_2[0x16] < 2) && (param_2[0x15] < 2)) && (param_2[0x14] < 4)) &&
          ((param_2[0x13] < 2 && (param_2[0x12] < 4)))) && (param_2[0x11] < 2)) &&
        (((param_2[0x10] < 2 && (param_2[0xf] < 2)) &&
         ((param_2[0xe] < 2 && (((param_2[0xd] < 2 && (param_2[0xc] < 2)) && (param_2[0xb] < 2))))))
        )) && ((param_2[10] < 2 && (param_2[9] < 2)))) &&
      ((param_2[8] < 2 &&
       (((param_2[7] < 2 && (param_2[6] < 2)) &&
        ((param_2[5] < 2 && (((param_2[4] < 2 && (param_2[3] < 2)) && (param_2[2] < 2)))))))))) &&
     ((param_2[1] < 8 && (*param_2 < 2)))) {
    iVar1 = tmOnuRegWrite(1,param_2[0x16] + param_2[0x15] * 2 + param_2[0x14] * 4 +
                            param_2[0x13] * 0x10 + param_2[0x12] * 0x20 + param_2[0x11] * 0x100 +
                            param_2[0x10] * 0x200 + param_2[0xf] * 0x400 + param_2[0xe] * 0x800 +
                            param_2[0xd] * 0x1000 + param_2[0xc] * 0x2000 + param_2[0xb] * 0x4000 +
                            param_2[10] * 0x8000 + param_2[9] * 0x10000 + param_2[8] * 0x20000 +
                            param_2[7] * 0x40000 + param_2[6] * 0x80000 + param_2[5] * 0x100000 +
                            param_2[4] * 0x200000 + param_2[3] * 0x400000 + param_2[2] * 0x800000 +
                            param_2[1] * 0x1000000 + *param_2 * 0x8000000,param_1,&smacRegTable);
    if ((iVar1 != 0) && (6 < g_tm_debug_level)) {
      printk("[TM][smac_set_efc]write reg failed!\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    iVar1 = 1;
  }
  else {
    printk("[TM][smac_set_cfg]input invalid parameter!\n");
    iVar1 = 1;
  }
  return iVar1;
}

