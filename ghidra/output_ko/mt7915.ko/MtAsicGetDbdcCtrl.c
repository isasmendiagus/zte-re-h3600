// module: mt7915.ko
// function: MtAsicGetDbdcCtrl @ 0x196bb0
// size: 448 bytes
//

undefined4 MtAsicGetDbdcCtrl(int param_1,byte *param_2)

{
  uint uVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint local_24 [2];
  
  local_24[0] = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0050,local_24);
  iVar3 = 0;
  param_2[9] = 0;
  param_2[0xc] = 0;
  param_2[0xf] = 0;
  param_2[8] = 7;
  param_2[4] = 0x3f;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  param_2[10] = (byte)((local_24[0] << 1) >> 0x1f);
  *param_2 = (byte)(local_24[0] >> 0x1f);
  param_2[0xd] = (byte)((local_24[0] << 2) >> 0x1f);
  param_2[0xb] = 5;
  param_2[0x10] = (byte)((local_24[0] << 5) >> 0x1f);
  param_2[0x12] = 1;
  param_2[0x13] = (byte)((local_24[0] << 4) >> 0x1f);
  param_2[0x15] = 2;
  param_2[0x16] = (byte)((local_24[0] << 3) >> 0x1f);
  param_2[0xe] = 6;
  param_2[0x11] = 6;
  param_2[0x14] = 6;
  pbVar2 = param_2;
  do {
    pbVar2[0x18] = (byte)iVar3;
    uVar4 = iVar3 + 0x16;
    iVar3 = iVar3 + 1;
    pbVar2[0x17] = 0;
    pbVar2[0x19] = (byte)(local_24[0] >> (uVar4 & 0xff)) & 1;
    pbVar2 = pbVar2 + 3;
  } while (iVar3 != 4);
  iVar3 = 0;
  param_2[0x24] = 0;
  param_2[0x23] = 1;
  param_2[0x26] = 1;
  param_2[0x27] = 1;
  param_2[0x25] = (byte)((local_24[0] << 0xb) >> 0x1f);
  param_2[0x28] = (byte)((local_24[0] << 10) >> 0x1f);
  pbVar2 = param_2;
  do {
    pbVar2[0x2a] = (byte)iVar3;
    uVar4 = iVar3 + 5;
    iVar3 = iVar3 + 1;
    pbVar2[0x29] = 3;
    pbVar2[0x2b] = (byte)(local_24[0] >> (uVar4 & 0xff)) & 1;
    pbVar2 = pbVar2 + 3;
  } while (iVar3 != 0xf);
  uVar4 = 0;
  pbVar2 = param_2;
  do {
    pbVar2[0x57] = (byte)uVar4;
    uVar1 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    pbVar2[0x56] = 2;
    pbVar2[0x58] = (byte)(local_24[0] >> uVar1) & 1;
    pbVar2 = pbVar2 + 3;
  } while (uVar4 != 5);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0054,local_24);
  uVar4 = 0;
  do {
    param_2[0x66] = (byte)uVar4;
    uVar1 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    param_2[0x65] = 4;
    param_2[0x67] = (byte)(local_24[0] >> uVar1) & 1;
    param_2 = param_2 + 3;
  } while (uVar4 != 0x20);
  return 0;
}

