// module: mt7915.ko
// function: fp_tx_flow_ctl @ 0xd401c
// size: 260 bytes
//

undefined4 fp_tx_flow_ctl(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_2 == 0) {
    _clear_bit(0,param_1 + 0x285b8c,param_3,0,param_4);
  }
  else {
    _set_bit(0,param_1 + 0x285b8c);
  }
  iVar5 = 0;
  do {
    iVar1 = iVar5 * 2;
    iVar4 = param_1 + iVar5 + 0x285b2c;
    OS_SPIN_LOCK_BH(iVar4);
    iVar3 = *(int *)(*(int *)(param_1 + 0x285b94) + iVar5 * 2);
    if (*(int *)(param_1 + 0x285b94) + iVar1 != iVar3) {
      do {
        piVar2 = (int *)(iVar3 + -0x4050);
        if (piVar2 == (int *)0x0) break;
        if (piVar2[0x1014] != 0) {
          *(int *)(piVar2[0x1014] + 4) = piVar2[0x1015];
        }
        if ((int *)piVar2[0x1015] != (int *)0x0) {
          *(int *)piVar2[0x1015] = piVar2[0x1014];
        }
        piVar2[0x1014] = 0;
        piVar2[0x1015] = 0;
        netif_tx_wake_queue(*(undefined4 *)(*piVar2 + 0x240));
        iVar3 = *(int *)(*(int *)(param_1 + 0x285b94) + iVar1);
      } while (*(int *)(param_1 + 0x285b94) + iVar1 != iVar3);
    }
    iVar5 = iVar5 + 4;
    OS_SPIN_UNLOCK_BH(iVar4);
    if (iVar5 == 8) {
      return 0;
    }
  } while( true );
}

