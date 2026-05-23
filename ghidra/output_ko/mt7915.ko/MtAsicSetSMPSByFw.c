// module: mt7915.ko
// function: MtAsicSetSMPSByFw @ 0x198d00
// size: 60 bytes
//

void MtAsicSetSMPSByFw(undefined4 param_1,undefined4 param_2,byte param_3)

{
  undefined2 local_10;
  undefined2 local_e;
  uint local_c;
  
  local_c = (uint)param_3;
  local_e = 8;
  local_10 = 0xd;
  CmdExtWtblUpdate(param_1,param_2,2,&local_10,8);
  return;
}

