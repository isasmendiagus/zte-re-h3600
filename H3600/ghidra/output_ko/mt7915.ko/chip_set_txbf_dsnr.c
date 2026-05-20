// module: mt7915.ko
// function: chip_set_txbf_dsnr @ 0x17c0ac
// size: 156 bytes
//

undefined4 chip_set_txbf_dsnr(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = hc_get_hdev_privdata();
  bVar1 = (byte)*param_3 & 0xf;
  *(byte *)(iVar2 + 0xa787a4) = *(byte *)(iVar2 + 0xa787a4) & 0xf0 | bVar1;
  *(byte *)(iVar2 + 0xa787a4) = bVar1 | (byte)((param_3[1] & 0xf) << 4);
  bVar1 = (byte)param_3[2] & 0xf;
  *(byte *)(iVar2 + 0xa787a5) = *(byte *)(iVar2 + 0xa787a5) & 0xf0 | bVar1;
  *(byte *)(iVar2 + 0xa787a5) = bVar1 | (byte)((param_3[3] & 0xf) << 4);
  bVar1 = (byte)param_3[4] & 0xf;
  *(byte *)(iVar2 + 0xa787a6) = *(byte *)(iVar2 + 0xa787a6) & 0xf0 | bVar1;
  *(byte *)(iVar2 + 0xa787a6) = bVar1 | (byte)((param_3[5] & 0xf) << 4);
  bVar1 = (byte)param_3[6] & 0xf;
  *(byte *)(iVar2 + 0xa787a7) = *(byte *)(iVar2 + 0xa787a7) & 0xf0 | bVar1;
  *(byte *)(iVar2 + 0xa787a7) = bVar1 | (byte)((param_3[7] & 0xf) << 4);
  return 1;
}

