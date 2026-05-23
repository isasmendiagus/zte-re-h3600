// module: mt7915.ko
// function: rtmp_ee_bin_init @ 0x128014
// size: 172 bytes
//

undefined4 rtmp_ee_bin_init(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  rtmp_ee_load_from_bin();
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    iVar2 = DebugLevel;
    iVar4 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
    uVar1 = *(ushort *)(iVar3 + 0x22c);
    uVar5 = (uint)*(ushort *)(iVar3 + 0xf4) + (uint)*(ushort *)(iVar3 + 0x22a) & 0xffff;
    *(uint *)("RTMPSetSTAPassPhrase" + param_1 + 4) = iVar4 + (uint)*(ushort *)(iVar3 + 0xf4);
    *(uint *)("RTMPSetSTAPassPhrase" + param_1 + 8) = iVar4 + uVar5;
    *(uint *)("RTMPSetSTAPassPhrase" + param_1 + 0x10) = iVar4 + (uVar5 + uVar1 & 0xffff);
    if (0 < iVar2) {
      printk(&_LC55);
    }
  }
  return 0;
}

