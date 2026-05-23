// module: mt7915.ko
// function: Set_Stop_Sounding_Proc @ 0xe5c64
// size: 48 bytes
//

bool Set_Stop_Sounding_Proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = mt_Trigger_Sounding_Packet(param_1,0,0,0,0,0);
  return iVar1 == 0;
}

