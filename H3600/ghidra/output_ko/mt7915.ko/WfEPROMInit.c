// module: mt7915.ko
// function: WfEPROMInit @ 0xb2ec0
// size: 48 bytes
//

int WfEPROMInit(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = WfEPROMSysInit();
  if (iVar1 != 0) {
    WfEPROMSysExit();
    return iVar1;
  }
  NICInitAsicFromEEPROM(param_1);
  return 0;
}

