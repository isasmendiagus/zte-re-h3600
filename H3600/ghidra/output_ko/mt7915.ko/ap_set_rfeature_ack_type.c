// module: mt7915.ko
// function: ap_set_rfeature_ack_type @ 0xcf240
// size: 40 bytes
//

void ap_set_rfeature_ack_type(undefined4 param_1,undefined1 *param_2)

{
  if (DebugLevel < 1) {
    return;
  }
  printk("func:%s, arg:%d \n","ap_set_rfeature_ack_type",*param_2);
  return;
}

