// module: mt7915.ko
// function: MT_ATESetPowerDropLevel @ 0x27e464
// size: 92 bytes
//

void MT_ATESetPowerDropLevel(int param_1,uint param_2)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (0 < DebugLevel) {
    printk("%s: PowerDropLevel:%d, control_band_idx:%d\n","MT_ATESetPowerDropLevel",param_2,uVar1);
  }
  MtCmdATESetPowerDropLevel(param_1,param_2 & 0xff,uVar1);
  return;
}

