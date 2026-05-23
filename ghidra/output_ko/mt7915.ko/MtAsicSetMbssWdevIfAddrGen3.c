// module: mt7915.ko
// function: MtAsicSetMbssWdevIfAddrGen3 @ 0x19ab14
// size: 692 bytes
//

void MtAsicSetMbssWdevIfAddrGen3(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *__s2;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_2e = 0;
  local_2c = 0;
  local_2a = 0;
  iVar3 = HcGetBandByWdev(param_2);
  iVar4 = *(int *)(param_2 + 4);
  iVar5 = *(int *)(iVar4 + 0x4060);
  uVar6 = (uint)(byte)(&DAT_003678f2)[param_1 + iVar3];
  bVar1 = (&DAT_003678f0)[param_1 + iVar3];
  mbss_fill_per_band_idx(param_1);
  iVar4 = *(int *)(iVar4 + 0x4064);
  if (2 < DebugLevel) {
    printk("%s: mbss_idx(%d), band(%d), grp_idx(%d), trans idx(%d)\n","MtAsicSetMbssWdevIfAddrGen3",
           iVar5,iVar3,iVar4,uVar6);
  }
  if (iVar4 == 0) {
    if (iVar5 == 0) {
      *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(param_1 + 0x794b5b);
      *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794b5f);
    }
    else {
      iVar7 = param_1 + (uVar6 - 1) * 6;
      __s2 = (undefined4 *)(iVar7 + 0x794b61);
      iVar4 = memcmp(&local_2e,__s2,6);
      if (iVar4 == 0) {
        iVar4 = param_1 + (iVar5 + -1) * 6;
        *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(param_1 + 0x794b5b);
        *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794b5f);
        *(byte *)(param_2 + 0x1b) = (char)iVar3 + 1U | *(byte *)(param_2 + 0x1b);
        *(undefined4 *)(iVar4 + 0x794b61) = *(undefined4 *)(param_2 + 0x1b);
        *(undefined2 *)(iVar4 + 0x794b65) = *(undefined2 *)(param_2 + 0x1f);
      }
      else {
        *(undefined4 *)(param_2 + 0x1b) = *__s2;
        *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(iVar7 + 0x794b65);
      }
    }
  }
  else {
    iVar5 = param_1 + (iVar5 + -1) * 6;
    iVar3 = memcmp(&local_2e,(undefined4 *)(iVar5 + 0x794b61),6);
    if (iVar3 == 0) {
      if (uVar6 == 0) {
        *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(param_1 + 0x794b5b);
        *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794b5f);
      }
      else {
        iVar3 = param_1 + (uVar6 - 1) * 6;
        *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(iVar3 + 0x794b61);
        *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(iVar3 + 0x794b65);
      }
      bVar2 = (byte)(1 << (bVar1 - 1 & 0xff));
      bVar1 = *(byte *)(param_2 + 0x20) & ~(bVar2 | bVar2 - 1);
      *(byte *)(param_2 + 0x20) = bVar1;
      *(byte *)(param_2 + 0x20) =
           bVar1 | (bVar2 | bVar2 - 1) & (char)iVar4 + *(char *)(param_1 + 0x794b60);
      *(undefined4 *)(iVar5 + 0x794b61) = *(undefined4 *)(param_2 + 0x1b);
      *(undefined2 *)(iVar5 + 0x794b65) = *(undefined2 *)(param_2 + 0x1f);
    }
    else {
      *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(iVar5 + 0x794b61);
      *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(iVar5 + 0x794b65);
    }
  }
  if (2 < DebugLevel) {
    printk("\tif_addr = %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_2 + 0x1b),
           *(undefined1 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x1d),
           *(undefined1 *)(param_2 + 0x1e),*(undefined1 *)(param_2 + 0x1f),
           *(undefined1 *)(param_2 + 0x20));
  }
  return;
}

