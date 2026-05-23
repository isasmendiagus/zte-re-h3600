// module: mt7915.ko
// function: twt_resource_dump @ 0x1678fc
// size: 64 bytes
//

void twt_resource_dump(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 != 0) {
    hc_get_hdev_ctrl();
    twt_ctrl_resource_status_dump();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: wdev=NULL, please check\n","twt_resource_dump",param_3,param_4);
  return;
}

