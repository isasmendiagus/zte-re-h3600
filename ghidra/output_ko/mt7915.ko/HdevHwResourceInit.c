// module: mt7915.ko
// function: HdevHwResourceInit @ 0xae18c
// size: 80 bytes
//

void HdevHwResourceInit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  os_zero_mem(param_1 + 0x1360,0x1f80);
  rc_init(param_1);
  wmm_ctrl_init(param_1,param_1 + 0x1a08);
  WtcInit(param_1);
  twt_ctrl_init(param_1);
  bss_color_table_init(param_1,extraout_r1,extraout_r2,param_4);
  return;
}

