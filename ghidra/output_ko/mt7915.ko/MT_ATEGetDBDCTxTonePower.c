// module: mt7915.ko
// function: MT_ATEGetDBDCTxTonePower @ 0x27e24c
// size: 96 bytes
//

void MT_ATEGetDBDCTxTonePower(int param_1,undefined4 param_2,uint param_3)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: AntIdx:%d, control_band_idx:%d\n","MT_ATEGetDBDCTxTonePower",param_3,uVar1);
  }
  MtCmdRfTestGetTxTonePower(param_1,param_2,param_3 & 0xff,uVar1);
  return;
}

