// module: mt7915.ko
// function: fp_ge_tx_deq_delay @ 0xd480c
// size: 300 bytes
//

undefined4 fp_ge_tx_deq_delay(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  longlong lVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = param_1 + param_2 * 0x58;
  if (((*(char *)(iVar5 + 0x9daea) != '\0') && (*(char *)(iVar5 + 0x9daeb) == '\0')) &&
     (iVar4 = param_1 + param_2 * 0x10, *(int *)(iVar4 + 0x285b54) == 0)) {
    iVar6 = param_1 + param_2 * 4 + 0x285b34;
    OS_SPIN_LOCK_BH(iVar6);
    iVar2 = *(int *)(param_1 + param_2 * 0x10 + 0x285b0c);
    if (iVar2 == 0) {
      OS_SPIN_UNLOCK_BH(iVar6);
      return 0;
    }
    OS_SPIN_UNLOCK_BH(iVar6);
    uVar3 = *(uint *)(iVar4 + 0x285b14);
    iVar4 = is_udp_packet(param_1,iVar2);
    if ((uVar3 != 0) && (uVar3 < *(uint *)(iVar5 + 0x9daec) && iVar4 == 0)) {
      if (*(char *)(iVar5 + 0x9dae9) == '\0') {
        lVar1 = (ulonglong)*(uint *)(iVar5 + 0x9daf8) * 0x10624dd3;
        RTMPSetTimer(param_1 + param_2 * 0x58 + 0x9dab4,*(uint *)(iVar5 + 0x9daf8) / 1000,(int)lVar1
                     ,(int)((ulonglong)lVar1 >> 0x20),param_4);
        *(undefined1 *)(iVar5 + 0x9dae9) = 1;
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

