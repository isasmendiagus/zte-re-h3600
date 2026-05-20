// module: mt7915.ko
// function: greenap_check_peer_connection_at_link_up_down @ 0x847a8
// size: 188 bytes
//

void greenap_check_peer_connection_at_link_up_down(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar2 = HcGetBandByWdev(param_2);
  uVar3 = IsHcGreenAPActiveByWdev(param_2);
  if (param_1 == -0x36da94) {
    return;
  }
  cVar1 = (&DAT_0036da94)[param_1];
  if (2 < DebugLevel) {
    printk("%s, greenap_cap=%d\n","greenap_check_peer_connection_at_link_up_down",cVar1 != '\0');
  }
  if (cVar1 == '\0') {
    return;
  }
  OS_SPIN_LOCK(&DAT_0036da9c + param_1);
  if (*(int *)(&DAT_0036da98 + param_1) == 0) {
    uVar4 = FUN_00083b10(param_1);
    FUN_00083c8c(param_1,uVar2,uVar3,uVar4);
  }
  OS_SPIN_UNLOCK(&DAT_0036da9c + param_1);
  return;
}

