// module: mt7915.ko
// function: MT_ATESetRXFilterPktLen @ 0x27d8c0
// size: 112 bytes
//

void MT_ATESetRXFilterPktLen(int param_1,uint param_2,undefined4 param_3)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: Enable:%d, control_band_idx:%d, RxPktLen:%d\n","MT_ATESetRXFilterPktLen",param_2,
           uVar1,param_3);
  }
  MtCmdRxFilterPktLen(param_1,param_2 & 0xff,uVar1,param_3);
  return;
}

