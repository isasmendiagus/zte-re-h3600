// module: idmfdb.ko
// function: get_node_index @ 0x10540
// size: 32 bytes
//

int get_node_index(void)

{
  int iVar1;
  
  iVar1 = WlanIndex2WlanIdmMap();
  if (iVar1 == 0) {
    iVar1 = 0xff;
  }
  else {
    iVar1 = (uint)*(byte *)(iVar1 + 0x26) + (uint)*(byte *)(iVar1 + 0x25) * 8;
  }
  return iVar1;
}

