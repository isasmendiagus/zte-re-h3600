// module: mt7915.ko
// function: fp_enq_dataq_pkt @ 0xd3cd8
// size: 436 bytes
//

undefined4 fp_enq_dataq_pkt(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar7 = *(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar8 = *(int *)(param_1 + 0x285ae8);
  iVar2 = wlan_operate_get_state(param_2);
  if (iVar2 == 1) {
    if (*(char *)(iVar1 + 0x20) == '\0') {
      uVar3 = 0;
    }
    else {
      uVar3 = HcGetBandByWdev(param_2);
      if (1 < uVar3) goto LAB_000d3d3c;
    }
    iVar9 = param_1 + uVar3 * 4 + 0x285b2c;
    iVar1 = uVar3 * 0x10;
    OS_SPIN_LOCK_BH(iVar9);
    iVar2 = param_1 + iVar1;
    uVar4 = (uint)*(ushort *)(iVar8 + 4);
    uVar6 = *(int *)(iVar2 + 0x285b14) + *(int *)(iVar2 + 0x285af4);
    if ((uVar6 < uVar4) || (uVar6 < uVar4 + *(ushort *)(iVar8 + 6))) {
      *param_3 = 0;
      puVar5 = *(undefined4 **)(param_1 + iVar1 + 0x285af0);
      if (puVar5 == (undefined4 *)0x0) {
        *(undefined4 **)(param_1 + iVar1 + 0x285aec) = param_3;
      }
      else {
        *puVar5 = param_3;
      }
      *(undefined4 **)(param_1 + iVar1 + 0x285af0) = param_3;
      *(int *)(iVar2 + 0x285af4) = *(int *)(iVar2 + 0x285af4) + 1;
      OS_SPIN_UNLOCK_BH(iVar9);
      iVar1 = param_1 + 0x9d000 + iVar1;
      *(int *)(iVar1 + 0xc90) = *(int *)(iVar1 + 0xc90) + 1;
      (**(code **)(iVar7 + 8))(param_1,0,uVar3);
      return 0;
    }
    OS_SPIN_UNLOCK_BH(iVar9);
    (**(code **)(iVar7 + 8))(param_1,0,uVar3);
    wlan_dbg_radio_statistics_inc(0,6);
  }
  else {
    wlan_dbg_set_last_error(0,0,0x308,"fp_enq_dataq_pkt");
  }
LAB_000d3d3c:
  *(int *)(param_1 + 0x9db68) = *(int *)(param_1 + 0x9db68) + 1;
  RTMPFreeNdisPacket(param_1,param_3);
  return 1;
}

