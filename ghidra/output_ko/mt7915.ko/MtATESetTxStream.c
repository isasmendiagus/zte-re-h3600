// module: mt7915.ko
// function: MtATESetTxStream @ 0x280c24
// size: 132 bytes
//

undefined4 MtATESetTxStream(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_58;
  undefined1 local_57;
  
  os_zero_mem(&local_5c,0x4c);
  local_5b = 4;
  local_58 = (undefined1)param_2;
  local_57 = (undefined1)param_3;
  local_5c = 1;
  uVar1 = MtCmdATETest(param_1,&local_5c);
  if (0 < DebugLevel) {
    printk("%s: StreamNum:%x BandIdx:%x\n","MtATESetTxStream",param_2,param_3);
  }
  return uVar1;
}

