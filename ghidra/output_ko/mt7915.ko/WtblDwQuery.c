// module: mt7915.ko
// function: WtblDwQuery @ 0x1c6288
// size: 76 bytes
//

undefined4 WtblDwQuery(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined2 local_18;
  undefined2 local_16;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = (uint)CONCAT11(param_4,param_3);
  local_10 = 0;
  local_c = 0;
  local_16 = 0x10;
  local_18 = 0xe;
  CmdExtWtblUpdate(param_1,param_2,3,&local_18,0x10);
  return local_c;
}

