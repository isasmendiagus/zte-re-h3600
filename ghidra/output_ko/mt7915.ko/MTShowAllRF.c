// module: mt7915.ko
// function: MTShowAllRF @ 0x1c829c
// size: 180 bytes
//

undefined4 MTShowAllRF(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_24 [2];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4 != 0) {
    uVar3 = 0;
    do {
      uVar2 = 0;
      do {
        MtCmdRFRegAccessRead(param_1,uVar3,uVar2,local_24);
        if (0 < DebugLevel) {
          printk("%s():%d 0x%04x 0x%08x\n","MTShowAllRF",uVar3,uVar2,local_24[0]);
        }
        uVar2 = uVar2 + 4;
      } while (uVar2 <= (uint)(*(int *)(iVar1 + 0x84) * 4));
      uVar3 = uVar3 + 1;
    } while (uVar3 < (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4);
  }
  return 1;
}

