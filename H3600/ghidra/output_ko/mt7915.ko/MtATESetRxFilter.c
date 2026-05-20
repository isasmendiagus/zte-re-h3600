// module: mt7915.ko
// function: MtATESetRxFilter @ 0x280d3c
// size: 152 bytes
//

undefined4
MtATESetRxFilter(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  char local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined4 local_54;
  
  local_62 = (undefined1)((uint)param_3 >> 0x10);
  os_zero_mem(&local_5c,0x4c,param_3,param_4,param_2);
  local_63 = 3;
  local_64 = (char)param_3;
  local_5c = 1;
  local_5b = 3;
  if (local_64 != '\0') {
    local_58 = 1;
    param_2 = 1;
  }
  else {
    local_63 = (undefined1)((uint)param_3 >> 8);
  }
  local_56 = local_62;
  if (local_64 == '\0') {
    local_57 = local_63;
    local_54 = param_2;
  }
  uVar1 = MtCmdATETest(param_1,&local_5c);
  if (0 < DebugLevel) {
    printk("%s: BandIdx:%x\n","MtATESetRxFilter",local_62);
  }
  return uVar1;
}

