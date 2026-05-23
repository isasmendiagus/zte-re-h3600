// module: mt7915.ko
// function: ap_set_rfeature_ppdu_tx_type @ 0xcf3a8
// size: 164 bytes
//

void ap_set_rfeature_ppdu_tx_type(undefined4 param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  cVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%d \n","ap_set_rfeature_ppdu_tx_type",cVar1);
  }
  if (cVar1 == '\x04') {
    return;
  }
  if (cVar1 == '\0') {
    SetMuruSuTx(param_1,&_LC10);
    pcVar2 = "dl_comm_user_cnt:0";
  }
  else {
    if (cVar1 != '\x01') {
      return;
    }
    SetMuruSuTx(param_1,&_LC11);
    pcVar2 = "dl_comm_user_cnt:2";
  }
  set_muru_manual_config(param_1,pcVar2);
  set_muru_manual_config(param_1,"update");
  return;
}

