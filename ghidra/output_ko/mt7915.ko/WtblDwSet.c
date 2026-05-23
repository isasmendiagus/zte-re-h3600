// module: mt7915.ko
// function: WtblDwSet @ 0x1c62d4
// size: 80 bytes
//

void WtblDwSet(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4,
              undefined4 param_5,undefined4 param_6)

{
  undefined2 local_20;
  undefined2 local_1e;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = (uint)CONCAT11(param_4,param_3);
  local_18 = param_5;
  local_14 = param_6;
  local_1e = 0x10;
  local_20 = 0xe;
  CmdExtWtblUpdate(param_1,param_2,2,&local_20,0x10);
  return;
}

