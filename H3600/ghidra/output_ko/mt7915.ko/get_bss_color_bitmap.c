// module: mt7915.ko
// function: get_bss_color_bitmap @ 0x206a04
// size: 32 bytes
//

void get_bss_color_bitmap
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  FUN_00206840();
  hc_bcolor_get_bitmap(param_1,param_2,extraout_r2,param_4);
  return;
}

