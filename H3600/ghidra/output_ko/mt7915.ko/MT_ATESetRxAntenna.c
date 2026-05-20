// module: mt7915.ko
// function: MT_ATESetRxAntenna @ 0x27c3c8
// size: 180 bytes
//

undefined4 MT_ATESetRxAntenna(int param_1,uint param_2)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar3 = net_ad_wrap_service();
  bVar2 = *(byte *)(iVar3 + 0x4cc);
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(byte *)(iVar3 + 0x6d) == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = 0;
    uVar5 = 0;
    do {
      uVar1 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      uVar4 = uVar4 | 1 << uVar1 & 0xffU;
    } while (uVar5 != *(byte *)(iVar3 + 0x6d));
    if ((uVar4 & param_2) != 0) {
      uVar4 = uVar4 & param_2;
    }
  }
  if (2 < DebugLevel) {
    printk("%s: Ant = 0x%x, control_band_idx = %d\n","MT_ATESetRxAntenna",uVar4,(uint)bVar2);
  }
  iVar3 = net_ad_wrap_service(param_1);
  *(short *)((uint)bVar2 * 0xd18 + iVar3 + 0x112e) = (short)uVar4;
  return 0;
}

