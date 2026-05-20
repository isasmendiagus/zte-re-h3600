// module: mt7915.ko
// function: tkip_sbox @ 0x11793c
// size: 56 bytes
//

uint tkip_sbox(uint param_1)

{
  uint uVar1;
  
  uVar1 = (param_1 << 0x10) >> 0x18;
  return *(int *)(Tkip_Sbox_Upper + uVar1 * 4) + *(int *)(Tkip_Sbox_Lower + uVar1 * 4) * 0x100 ^
         *(int *)(Tkip_Sbox_Lower + (param_1 & 0xff) * 4) +
         *(int *)(Tkip_Sbox_Upper + (param_1 & 0xff) * 4) * 0x100;
}

