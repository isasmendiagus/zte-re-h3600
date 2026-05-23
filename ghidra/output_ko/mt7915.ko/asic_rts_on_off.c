// module: mt7915.ko
// function: asic_rts_on_off @ 0x135a98
// size: 164 bytes
//

undefined4 asic_rts_on_off(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  code *pcVar4;
  int iVar5;
  undefined4 uVar6;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    iVar5 = *(int *)(param_1 + 8);
    uVar1 = HcGetBandByWdev(param_1);
    iVar2 = hc_get_arch_ops(*(undefined4 *)(iVar5 + 0xa797a0));
    pcVar4 = *(code **)(iVar2 + 0x1cc);
    if (pcVar4 == (code *)0x0) {
      AsicNotSupportFunc(iVar5,"asic_rts_on_off");
      uVar1 = 0;
    }
    else {
      if (param_2 == 0) {
        uVar3 = 0xffffff;
        uVar6 = 0xff;
      }
      else {
        uVar6 = wlan_operate_get_rts_pkt_thld(param_1);
        uVar3 = wlan_operate_get_rts_len_thld(param_1);
        pcVar4 = *(code **)(iVar2 + 0x1cc);
      }
      uVar1 = (*pcVar4)(iVar5,uVar1,uVar6,uVar3,param_2);
    }
  }
  return uVar1;
}

