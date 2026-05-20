// module: mt7915.ko
// function: token_tx_get_queue_by_band @ 0x1d3f58
// size: 28 bytes
//

char * token_tx_get_queue_by_band(char *param_1,int param_2)

{
  if (*param_1 == '\x02') {
    param_1 = param_1 + param_2 * 0xa8;
  }
  return param_1 + 4;
}

