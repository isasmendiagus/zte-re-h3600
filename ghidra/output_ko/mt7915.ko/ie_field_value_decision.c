// module: mt7915.ko
// function: ie_field_value_decision @ 0x139ac4
// size: 20 bytes
//

void ie_field_value_decision(undefined4 param_1,int param_2)

{
  if ((*(uint *)(param_2 + 0xa8) & 0x10) == 0) {
    return;
  }
  he_mac_cap_af_decision(param_1,*(undefined4 *)(param_2 + 0x122));
  return;
}

