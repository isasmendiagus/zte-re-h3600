// module: mt7915.ko
// function: ParseTxSPacket_v2 @ 0x1e0104
// size: 176 bytes
//

undefined4 ParseTxSPacket_v2(int param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 == 0) {
    if ((*(byte *)(param_4 + 2) & 0x7f) != 0) {
      asic_dump_txs(param_1,0,param_4,param_4,param_4);
      return 0xffffffff;
    }
  }
  else if (((param_3 == 1) &&
           ((((*(uint *)(param_1 + 0xa3ac14) & 1) != 0 ||
             ((*(int *)(param_1 + 0xa77bb4) == 1 &&
              ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) &&
            (*(char *)(param_1 + 0xa3b8b5) != '\0')))) &&
          ((*(uint *)(param_1 + 0xa39ffc) & 0x100) != 0)) {
    asic_dump_txs(param_1,1,param_4,param_4,param_4);
    return 0;
  }
  return 0;
}

