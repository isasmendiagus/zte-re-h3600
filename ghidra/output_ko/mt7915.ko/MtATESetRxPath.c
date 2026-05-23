// module: mt7915.ko
// function: MtATESetRxPath @ 0x280cac
// size: 140 bytes
//

undefined4 MtATESetRxPath(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_58;
  undefined1 local_57;
  
  os_zero_mem(&local_5c,0x4c);
  if (param_3 != 0) {
    param_2 = param_2 << 2;
  }
  local_5b = 2;
  local_5c = 1;
  local_58 = (undefined1)param_2;
  local_57 = (undefined1)param_3;
  uVar1 = MtCmdATETest(param_1,&local_5c);
  if (0 < DebugLevel) {
    printk("%s: RxPathSel:%x BandIdx:%x\n","MtATESetRxPath",param_2,param_3);
  }
  return uVar1;
}

