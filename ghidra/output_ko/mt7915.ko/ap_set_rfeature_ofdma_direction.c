// module: mt7915.ko
// function: ap_set_rfeature_ofdma_direction @ 0xcebf4
// size: 84 bytes
//

void ap_set_rfeature_ofdma_direction(undefined4 param_1,char *param_2)

{
  char cVar1;
  
  cVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%u \n","ap_set_rfeature_ofdma_direction",cVar1);
  }
  if (cVar1 != '\x03') {
    return;
  }
  SetMuru20MDynAlgo(param_1,&_LC10);
  return;
}

