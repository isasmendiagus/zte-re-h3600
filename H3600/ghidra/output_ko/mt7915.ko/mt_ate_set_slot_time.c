// module: mt7915.ko
// function: mt_ate_set_slot_time @ 0x27e528
// size: 124 bytes
//

void mt_ate_set_slot_time(int param_1,uint param_2,uint param_3)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: SlotTime:%d, SifsTime:%d, control_band_idx:%d\n","mt_ate_set_slot_time",param_2,
           param_3,uVar1);
  }
  MtCmdATESetSlotTime(param_1,param_2 & 0xff,param_3 & 0xff,2,0x3c,uVar1);
  return;
}

