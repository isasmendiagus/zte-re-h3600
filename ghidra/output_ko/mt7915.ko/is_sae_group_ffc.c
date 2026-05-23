// module: mt7915.ko
// function: is_sae_group_ffc @ 0x20bd88
// size: 32 bytes
//

undefined4 is_sae_group_ffc(undefined4 param_1)

{
  switch(param_1) {
  case 1:
  case 2:
  case 5:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x16:
  case 0x17:
  case 0x18:
    return 1;
  default:
    return 0;
  }
}

