// module: mt7915.ko
// function: get_max_nss_by_htcap_ie_mcs @ 0x137a80
// size: 72 bytes
//

uint get_max_nss_by_htcap_ie_mcs(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0x20;
  do {
    uVar2 = uVar2 - 1 & 0xff;
    uVar1 = uVar2 >> 3;
  } while (uVar2 != 0 && ((uint)*(byte *)(param_1 + uVar1) & 1 << (uVar2 + uVar1 * -8 & 0xff)) == 0)
  ;
  return uVar1;
}

