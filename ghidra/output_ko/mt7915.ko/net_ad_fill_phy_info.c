// module: mt7915.ko
// function: net_ad_fill_phy_info @ 0x25c328
// size: 236 bytes
//

undefined4 net_ad_fill_phy_info(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  
  sys_ad_zero_mem(param_1 + 0xc4,0x1c,param_3,param_4,param_4);
  bVar2 = *(byte *)(param_2 + 2);
  *(byte *)(param_1 + 0xc4) = bVar2;
  *(undefined1 *)(param_1 + 0xcb) = *(undefined1 *)(param_2 + 10);
  *(undefined1 *)(param_1 + 0xcc) = *(undefined1 *)(param_2 + 0xb);
  *(undefined1 *)(param_1 + 200) = *(undefined1 *)(param_2 + 4);
  *(undefined1 *)(param_1 + 199) = *(undefined1 *)(param_2 + 5);
  *(undefined1 *)(param_1 + 0xc6) = *(undefined1 *)(param_2 + 3);
  *(undefined1 *)(param_1 + 0xcd) = *(undefined1 *)(param_2 + 9);
  *(undefined1 *)(param_1 + 0xc9) = *(undefined1 *)(param_2 + 7);
  *(undefined1 *)(param_1 + 0xca) = *(undefined1 *)(param_2 + 6);
  if (bVar2 < 5) {
    *(uint *)(param_1 + 0xd0) = *(byte *)(param_2 + 8) & 0x1f;
    if (bVar2 == 0) {
      bVar2 = *(byte *)(param_2 + 8);
      uVar3 = bVar2 & 3;
      *(uint *)(param_1 + 0xd0) = uVar3;
      uVar1 = uVar3;
      if ((bVar2 & 3) != 0) {
        uVar1 = 1;
      }
      if ((uVar1 & *(byte *)(param_2 + 8) >> 3) != 0) {
        *(uint *)(param_1 + 0xd0) = uVar3 - 1;
      }
      return 0;
    }
  }
  else {
    *(uint *)(param_1 + 0xd0) = *(byte *)(param_2 + 8) & 0xf;
    *(byte *)(param_1 + 0xd4) = (byte)(((uint)*(byte *)(param_2 + 8) << 0x1a) >> 0x1f);
    if (bVar2 == 9) {
      bVar2 = *(byte *)(param_2 + 8) & 0x10;
      if ((*(byte *)(param_2 + 8) & 0x10) != 0) {
        bVar2 = 1;
      }
      *(byte *)(param_1 + 0xd5) = bVar2;
      return 0;
    }
  }
  return 0;
}

