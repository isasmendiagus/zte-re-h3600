// module: mt7915.ko
// function: token_tx_get_queue_by_token_id @ 0x1d3f74
// size: 44 bytes
//

char * token_tx_get_queue_by_token_id(char *param_1,uint param_2)

{
  if ((*param_1 == '\x02') && (*(uint *)(param_1 + 0x14) < param_2)) {
    return param_1 + 0xac;
  }
  return param_1 + 4;
}

