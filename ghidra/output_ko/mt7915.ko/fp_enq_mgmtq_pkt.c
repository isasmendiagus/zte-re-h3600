// module: mt7915.ko
// function: fp_enq_mgmtq_pkt @ 0xd3e8c
// size: 396 bytes
//

undefined4 fp_enq_mgmtq_pkt(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = *(int *)(param_1 + 0x285ae8);
  iVar2 = wlan_operate_get_state(param_2);
  if (iVar2 == 1) {
    if (*(char *)(iVar1 + 0x20) == '\0') {
      uVar3 = 0;
    }
    else {
      uVar3 = HcGetBandByWdev(param_2);
      if (1 < uVar3) goto LAB_000d3eec;
    }
    iVar1 = param_1 + uVar3 * 4 + 0x285b3c;
    OS_SPIN_LOCK_BH(iVar1);
    iVar2 = param_1 + uVar3 * 0x10;
    if ((uint)(*(int *)(iVar2 + 0x285b74) + *(int *)(iVar2 + 0x285b54)) <
        (uint)*(ushort *)(iVar5 + 2)) {
      *param_3 = 0;
      if (*(undefined4 **)(iVar2 + 0x285b50) == (undefined4 *)0x0) {
        *(undefined4 **)(iVar2 + 0x285b4c) = param_3;
      }
      else {
        **(undefined4 **)(iVar2 + 0x285b50) = param_3;
      }
      *(undefined4 **)(param_1 + uVar3 * 0x10 + 0x285b50) = param_3;
      *(int *)(iVar2 + 0x285b54) = *(int *)(iVar2 + 0x285b54) + 1;
      OS_SPIN_UNLOCK_BH(iVar1);
      (**(code **)(iVar4 + 8))(param_1,0,uVar3);
      return 0;
    }
    OS_SPIN_UNLOCK_BH(iVar1);
    (**(code **)(iVar4 + 8))(param_1,0,uVar3);
    wlan_dbg_radio_statistics_inc(0,3);
  }
  else {
    wlan_dbg_set_last_error(0,0,0x290,"fp_enq_mgmtq_pkt");
  }
LAB_000d3eec:
  *(int *)(param_1 + 0x9db6c) = *(int *)(param_1 + 0x9db6c) + 1;
  RTMPFreeNdisPacket(param_1,param_3);
  return 1;
}

