// module: mt7915.ko
// function: MT_ATEGenBurstPkt @ 0x2863ec
// size: 268 bytes
//

undefined4 MT_ATEGenBurstPkt(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar2 = net_ad_wrap_service();
  iVar3 = *(int *)(iVar2 + param_3 * 0xd18 + 0x504);
  iVar2 = net_ad_wrap_service(param_1);
  iVar2 = iVar2 + param_3 * 0xd18;
  uVar4 = *(undefined4 *)(iVar2 + 0x10f4);
  cVar1 = *(char *)(iVar2 + 0x1106);
  if (2 < DebugLevel) {
    printk("%s: new_txlen/new_hlen=%d/%d, qos/amsdu/ampdu=%d/%d/%d\n","MT_ATEGenBurstPkt",uVar4,
           *(undefined4 *)(iVar2 + 0x10fc),*(undefined1 *)(iVar2 + 0x1104),
           *(undefined1 *)(iVar2 + 0x1105),cVar1);
  }
  if (cVar1 != '\0') {
    if (*(int *)(*(int *)(iVar3 + 0x904) + 0xb0) == 0) {
      iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar2 + 0x1e8) == (code *)0x0) {
        return 0;
      }
      (**(code **)(iVar2 + 0x1e8))(param_1,param_3);
    }
    uVar4 = mt_ate_ampdu_frame(param_1,param_2,param_3);
    return uVar4;
  }
  *(undefined4 *)(iVar2 + 0x10f8) = uVar4;
  *(undefined4 *)(iVar2 + 0x1100) = 1;
  uVar4 = mt_ate_non_ampdu_frame(param_1,param_2,param_3);
  return uVar4;
}

