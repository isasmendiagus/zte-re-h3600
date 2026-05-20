// module: mt7915.ko
// function: ap_set_rfeature_dis_trig_type @ 0xcf450
// size: 120 bytes
//

void ap_set_rfeature_dis_trig_type(undefined4 param_1,byte *param_2)

{
  byte bVar1;
  undefined4 local_1e;
  undefined4 local_1a;
  undefined4 local_16;
  undefined2 local_12;
  
  bVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%u \n","ap_set_rfeature_dis_trig_type",bVar1);
  }
  if ((bVar1 & 0xfb) == 0) {
    local_1e = 0x2d302d30;
    local_1a = 0x37362d35;
    local_12 = 0x33;
    local_16 = 0x3230352d;
    SetMuruBsrpCtrl(param_1,&local_1e);
  }
  return;
}

