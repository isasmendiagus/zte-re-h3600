// module: mt7915.ko
// function: ap_set_rfeature_trig_type @ 0xcf4cc
// size: 192 bytes
//

void ap_set_rfeature_trig_type(undefined4 param_1,byte *param_2)

{
  byte bVar1;
  undefined4 local_1e;
  undefined4 local_1a;
  undefined *local_16;
  undefined2 local_12;
  
  bVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%d \n","ap_set_rfeature_trig_type",bVar1);
  }
  set_muru_trig_type(param_1,bVar1);
  if ((bVar1 & 0xfb) != 0) {
    if (bVar1 != 1) {
      return;
    }
    local_1e = 0x303a3130;
    local_1a = 0x30303a30;
    local_16 = &DAT_0042313a;
    Set_TxBfTxSndInfo(param_1,&local_1e,&DAT_0042313a,&_LC28);
    return;
  }
  local_1e = 0x2d302d31;
  local_1a = 0x37362d35;
  local_12 = 0x33;
  local_16 = (undefined *)0x3230352d;
  SetMuruBsrpCtrl(param_1,&local_1e);
  return;
}

