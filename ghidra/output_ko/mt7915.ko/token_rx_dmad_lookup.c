// module: mt7915.ko
// function: token_rx_dmad_lookup @ 0x1d3aac
// size: 68 bytes
//

undefined4
token_rx_dmad_lookup
          (int *param_1,int param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5)

{
  *param_3 = *(undefined4 *)(*param_1 + param_2 * 0x20);
  *param_4 = *(undefined4 *)(*param_1 + param_2 * 0x20 + 8);
  *param_5 = *(undefined4 *)(*param_1 + param_2 * 0x20 + 0xc);
  return 0;
}

