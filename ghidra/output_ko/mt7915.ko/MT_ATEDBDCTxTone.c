// module: mt7915.ko
// function: MT_ATEDBDCTxTone @ 0x27e370
// size: 152 bytes
//

undefined4
MT_ATEDBDCTxTone(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                undefined1 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATEDBDCTxTone");
  }
  MtCmdTxTone(param_1,uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return 0;
}

