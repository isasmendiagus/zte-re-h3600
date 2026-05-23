// module: mt7915.ko
// function: MT_ATEGetTxFreqOffset @ 0x27e6cc
// size: 76 bytes
//

undefined4 MT_ATEGetTxFreqOffset(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char cVar2;
  
  cVar2 = *(char *)(param_1 + 0xa3ae36);
  if (*(char *)(param_1 + 0x79504d) == '\0' && cVar2 == '\x01') {
    cVar2 = '\0';
    *(undefined1 *)(param_1 + 0xa3ae36) = 0;
  }
  uVar1 = MtCmdGetFreqOffset(param_1,cVar2,param_2);
  os_msec_delay(0x1e);
  return uVar1;
}

