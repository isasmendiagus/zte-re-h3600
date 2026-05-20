// module: mt7915.ko
// function: Show_available_BwCh_Proc @ 0x2374e8
// size: 112 bytes
//

undefined4
Show_available_BwCh_Proc
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  if (0 < DebugLevel) {
    printk("band_idx: %d\n",0,param_3,DebugLevel,param_4);
  }
  DfsProvideAvailableChList(param_1,0);
  if (0 < DebugLevel) {
    printk("band_idx: %d\n",1,extraout_r2,DebugLevel,param_4);
  }
  DfsProvideAvailableChList(param_1,1);
  return 1;
}

