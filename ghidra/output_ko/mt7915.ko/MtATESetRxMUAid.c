// module: mt7915.ko
// function: MtATESetRxMUAid @ 0x280240
// size: 128 bytes
//

void MtATESetRxMUAid(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_59;
  undefined4 local_58;
  undefined2 local_54;
  
  os_zero_mem(&local_5c,0x4c);
  local_5b = 0x1e;
  local_54 = (undefined2)param_3;
  local_5c = 1;
  local_59 = 0xf;
  local_58 = param_2;
  if (0 < DebugLevel) {
    printk("%s: Set to decode MU accodring to AID:%d (61696 means disable)\n","MtATESetRxMUAid",
           param_3);
  }
  MtCmdATETest(param_1,&local_5c);
  return;
}

