// module: mt7915.ko
// function: MT_ATESetDBDCTxTonePower @ 0x27e2b0
// size: 188 bytes
//

undefined4 MT_ATESetDBDCTxTonePower(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  uVar3 = param_4;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
    uVar2 = 0;
    do {
      uVar3 = uVar2;
      if ((param_4 >> (uVar2 & 0xff) & 1) != 0) break;
      uVar2 = uVar2 + 1;
      uVar3 = param_4;
    } while (uVar2 != 4);
  }
  if (2 < DebugLevel) {
    printk("%s: pwr1:%d, pwr2:%d, AntIdx:%d, control_band_idx:%d\n","MT_ATESetDBDCTxTonePower",
           param_2,param_3,uVar3,uVar1);
  }
  MtCmdTxTonePower(param_1,0x12,param_3,uVar3 & 0xff,uVar1);
  return 0;
}

