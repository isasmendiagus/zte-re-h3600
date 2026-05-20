// module: mt7915.ko
// function: MT_ATESetCfgOnOff @ 0x27d960
// size: 112 bytes
//

void MT_ATESetCfgOnOff(int param_1,uint param_2,uint param_3)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: Type:%d, Enable:%d, control_band_idx:%d\n","MT_ATESetCfgOnOff",param_2,param_3,uVar1
          );
  }
  MtCmdCfgOnOff(param_1,param_2 & 0xff,param_3 & 0xff,uVar1);
  return;
}

