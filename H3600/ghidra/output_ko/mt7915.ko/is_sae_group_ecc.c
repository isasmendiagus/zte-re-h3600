// module: mt7915.ko
// function: is_sae_group_ecc @ 0x20bd38
// size: 32 bytes
//

undefined4 is_sae_group_ecc(undefined4 param_1)

{
  switch(param_1) {
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
    return 1;
  default:
    return 0;
  }
}

