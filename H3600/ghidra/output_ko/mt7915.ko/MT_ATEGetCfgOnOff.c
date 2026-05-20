// module: mt7915.ko
// function: MT_ATEGetCfgOnOff @ 0x27d934
// size: 44 bytes
//

undefined4 MT_ATEGetCfgOnOff(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = MtCmdGetCfgOnOff(param_1,param_2,*(undefined1 *)(param_1 + 0xa3ae36),param_3);
  os_msec_delay(0x1e);
  return uVar1;
}

