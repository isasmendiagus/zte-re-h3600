// module: mt7915.ko
// function: mt7915_rssi_get @ 0x1797dc
// size: 132 bytes
//

void mt7915_rssi_get(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char local_14;
  char local_13;
  char local_12;
  char local_11;
  
  MtCmdGetRssi(param_1,param_2,&local_14);
  *param_3 = local_14;
  param_3[1] = local_13;
  param_3[2] = local_12;
  param_3[3] = local_11;
  if (3 < DebugLevel) {
    printk("%s(): wcid: %d, rssi: %d, %d, %d, %d \n","mt7915_rssi_get",param_2,(int)local_14,
           (int)local_13,(int)local_12,(int)local_11);
  }
  return;
}

