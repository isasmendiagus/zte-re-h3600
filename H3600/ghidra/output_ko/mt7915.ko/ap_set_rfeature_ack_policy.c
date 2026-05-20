// module: mt7915.ko
// function: ap_set_rfeature_ack_policy @ 0xced00
// size: 72 bytes
//

void ap_set_rfeature_ack_policy(undefined4 param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  uVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%d \n","ap_set_rfeature_ack_policy",uVar1);
  }
  set_muru_mudl_ack_policy(param_1,uVar1);
  return;
}

