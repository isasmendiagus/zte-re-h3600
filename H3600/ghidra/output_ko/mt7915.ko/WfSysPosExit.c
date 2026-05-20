// module: mt7915.ko
// function: WfSysPosExit @ 0xb30f4
// size: 36 bytes
//

undefined4 WfSysPosExit(undefined4 param_1)

{
  WfEPROMSysExit();
  WfMcuSysExit(param_1);
  WfHifSysExit(param_1);
  return 0;
}

