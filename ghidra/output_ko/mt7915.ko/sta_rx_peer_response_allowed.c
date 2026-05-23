// module: mt7915.ko
// function: sta_rx_peer_response_allowed @ 0x79acc
// size: 136 bytes
//

bool sta_rx_peer_response_allowed(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetStaCfgByWdev();
  iVar2 = memcmp((void *)(param_3 + 6),(void *)(iVar1 + 0x212428),6);
  if ((((uint)*(byte *)(iVar1 + 0x212426) != (uint)*(byte *)(param_3 + 0x2c)) ||
      (iVar1 = memcmp((void *)(param_3 + 0xc),(void *)(iVar1 + 0x212406),
                      (uint)*(byte *)(iVar1 + 0x212426)), iVar1 != 0)) && (iVar2 != 0)) {
    return false;
  }
  iVar1 = cntl_do_disassoc_now(param_2);
  return iVar1 == 0;
}

