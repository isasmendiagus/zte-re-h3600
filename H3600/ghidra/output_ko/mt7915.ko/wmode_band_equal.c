// module: mt7915.ko
// function: wmode_band_equal @ 0xb8288
// size: 152 bytes
//

uint wmode_band_equal(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if ((((param_1 & 0xb1) == 0) == ((param_2 & 0xb1) != 0)) ||
     (((param_1 & 0x4e) == 0) == ((param_2 & 0x4e) != 0))) {
    uVar3 = 0;
  }
  else {
    uVar3 = ((param_1 ^ 0x100 ^ param_2) << 0x17) >> 0x1f;
  }
  iVar1 = wmode_2_str();
  iVar2 = wmode_2_str(param_2);
  if (iVar1 != 0) {
    os_free_mem(iVar1);
  }
  if (iVar2 != 0) {
    os_free_mem(iVar2);
  }
  return uVar3;
}

