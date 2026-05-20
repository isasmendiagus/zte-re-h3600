// module: mt7915.ko
// function: RtmpPhyNetDevExit @ 0x246870
// size: 112 bytes
//

undefined4 RtmpPhyNetDevExit(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  wpf_exit();
  RT28xx_MBSS_Remove(param_1);
  RT28xx_MSTA_Remove(param_1);
  if (param_2 != 0) {
    if (-1 < DebugLevel) {
      printk("RtmpOSNetDevDetach(): RtmpOSNetDeviceDetach(), dev->name=%s!\n",param_2,extraout_r2,
             DebugLevel,param_4);
    }
    RtmpOSNetDevProtect(1);
    RtmpOSNetDevDetach(param_2);
    RtmpOSNetDevProtect(0);
  }
  return 1;
}

