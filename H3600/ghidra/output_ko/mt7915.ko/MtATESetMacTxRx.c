// module: mt7915.ko
// function: MtATESetMacTxRx @ 0x2802c4
// size: 140 bytes
//

void MtATESetMacTxRx(undefined4 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_61;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  
  os_zero_mem(&local_64,0x4c);
  local_5f = (undefined1)param_3;
  local_5e = (undefined1)param_4;
  local_64 = 1;
  local_63 = 1;
  local_61 = 0xf;
  local_60 = param_2;
  if (0 < DebugLevel) {
    printk("%s: TxRx:%x, Enable:%x, BandIdx:%x\n","MtATESetMacTxRx",param_2,param_3,param_4);
  }
  MtCmdATETest(param_1,&local_64);
  return;
}

