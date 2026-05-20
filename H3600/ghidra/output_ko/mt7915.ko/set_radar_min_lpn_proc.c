// module: mt7915.ko
// function: set_radar_min_lpn_proc @ 0x1015ec
// size: 148 bytes
//

undefined4
set_radar_min_lpn_proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  uVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  if (uVar1 < 0x21) {
    if (-1 < DebugLevel) {
      printk("%s():LPN Update %d \n","set_radar_min_lpn_proc",uVar1);
    }
    *(ushort *)(param_1 + 0x795434) = uVar1;
    mt_cmd_set_fcc5_min_lpn(param_1,uVar1);
  }
  else if (-1 < DebugLevel) {
    printk("%s():Invalid LPN value %d, please set in range 0 to 32\n","set_radar_min_lpn_proc",uVar1
          );
  }
  return 1;
}

