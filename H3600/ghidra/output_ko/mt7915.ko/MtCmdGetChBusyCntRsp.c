// module: mt7915.ko
// function: MtCmdGetChBusyCntRsp @ 0x1ab408
// size: 16 bytes
//

void MtCmdGetChBusyCntRsp(int param_1,int param_2)

{
  **(undefined4 **)(param_1 + 0xc) = *(undefined4 *)(param_2 + 4);
  return;
}

