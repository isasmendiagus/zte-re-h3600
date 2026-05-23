// module: mt7915.ko
// function: WfEPROMSysExit @ 0x13a314
// size: 28 bytes
//

undefined4 WfEPROMSysExit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  hc_radio_exit(param_1,*(undefined1 *)(param_1 + 0x79504d),param_3,param_1 + 0x795000,param_4);
  return 0;
}

