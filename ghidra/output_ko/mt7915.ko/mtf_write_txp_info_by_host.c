// module: mt7915.ko
// function: mtf_write_txp_info_by_host @ 0x19e6ac
// size: 460 bytes
//

undefined4 mtf_write_txp_info_by_host(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  uVar2 = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = HcGetBandByWdev(*(undefined4 *)(param_3 + 0x10));
  uVar2 = token_tx_get_queue_by_band(uVar2,uVar3);
  if (*(byte *)(param_3 + 0x2e) < 2) {
    if (*(byte *)(param_3 + 3) < 5) {
      __memzero(param_2,0x20);
      *(undefined1 *)(param_3 + 0x38) = 0x20;
    }
    else {
      __memzero(param_2,0x60);
      *(undefined1 *)(param_3 + 0x38) = 0x60;
    }
  }
  bVar1 = *(byte *)(param_3 + 0x2d);
  uVar4 = (uint)bVar1;
  if (uVar4 < 4) {
    iVar6 = param_2 + (uint)(bVar1 >> 1) * 0xc;
  }
  else {
    param_2 = param_2 + 0x20;
    iVar6 = param_2 + ((int)(uVar4 - 4) >> 1) * 0xc;
  }
  if ((bVar1 & 1) == 0) {
    uVar3 = RtmpDrvPciMapSingle(param_1,param_3,uVar4 & 1,1,0xff00);
    *(undefined4 *)(iVar6 + 8) = uVar3;
    iVar7 = *(int *)(param_3 + 0xc);
    if ((*(byte *)(iVar7 + 0x3a) & 8) == 0) {
      uVar5 = 1;
    }
    else {
      uVar5 = 2;
    }
    iVar7 = token_tx_enq(param_1,uVar2,iVar7,uVar5,*(undefined2 *)(param_3 + 0x1e),uVar3,
                         *(undefined4 *)(iVar7 + 100));
    *(ushort *)(iVar6 + 0xc) =
         ~((ushort)~(ushort)(((*(uint *)(param_3 + 0x28) & 0xfff) << 0x11) >> 0x10) >> 1);
  }
  else {
    uVar3 = RtmpDrvPciMapSingle(param_1,param_3,0,1,0xff00);
    *(undefined4 *)(iVar6 + 0x10) = uVar3;
    iVar7 = *(int *)(param_3 + 0xc);
    if ((*(byte *)(iVar7 + 0x3a) & 8) == 0) {
      uVar5 = 1;
    }
    else {
      uVar5 = 2;
    }
    iVar7 = token_tx_enq(param_1,uVar2,iVar7,uVar5,*(undefined2 *)(param_3 + 0x1e),uVar3,
                         *(undefined4 *)(iVar7 + 100));
    *(ushort *)(iVar6 + 0xe) =
         ~((ushort)~(ushort)(((*(uint *)(param_3 + 0x28) & 0xfff) << 0x11) >> 0x10) >> 1);
  }
  uVar4 = (uint)*(byte *)(param_3 + 0x2d);
  if (uVar4 < 4) {
    *(ushort *)(param_2 + uVar4 * 2) = ~((ushort)~(ushort)((uint)(iVar7 << 0x11) >> 0x10) >> 1);
  }
  else {
    *(ushort *)(param_2 + uVar4 * 2 + -8) = ~((ushort)~(ushort)((uint)(iVar7 << 0x11) >> 0x10) >> 1)
    ;
  }
  return 0;
}

