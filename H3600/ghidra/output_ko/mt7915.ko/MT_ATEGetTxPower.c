// module: mt7915.ko
// function: MT_ATEGetTxPower @ 0x27d810
// size: 172 bytes
//

undefined4 MT_ATEGetTxPower(int param_1,uint param_2,undefined4 param_3,uint param_4,uint *param_5)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined1 uStack_24;
  byte local_23;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: Channel: %d, u1BandIdx: %d, u4AntIdx: %d\n","MT_ATEGetTxPower",param_2,uVar1,param_4
          );
  }
  uVar2 = MtCmdGetTxPower(param_1,uVar1,param_2 & 0xff,param_4 & 0xff,&uStack_24);
  *param_5 = (uint)local_23;
  if (2 < DebugLevel) {
    printk("%s: Power: 0x%x\n","MT_ATEGetTxPower");
  }
  return uVar2;
}

