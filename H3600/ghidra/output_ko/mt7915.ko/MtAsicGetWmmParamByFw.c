// module: mt7915.ko
// function: MtAsicGetWmmParamByFw @ 0x199730
// size: 132 bytes
//

uint MtAsicGetWmmParamByFw(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined1 local_d4;
  undefined1 local_d3;
  undefined1 local_d0;
  byte local_ce;
  byte local_cd;
  ushort local_cc;
  ushort local_ca;
  
  os_zero_mem(&local_d4,0xc4);
  local_d4 = 1;
  local_d3 = 1;
  local_d0 = param_2;
  MtCmdGetEdca(param_1,&local_d4);
  switch(param_3) {
  case 0:
    return (uint)local_ca;
  case 1:
    return (uint)local_ce;
  case 2:
    return (uint)local_cd;
  case 3:
    uVar1 = (uint)local_cc;
    break;
  default:
    uVar1 = 0xdeadbeef;
  }
  return uVar1;
}

