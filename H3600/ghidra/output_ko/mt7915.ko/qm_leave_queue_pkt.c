// module: mt7915.ko
// function: qm_leave_queue_pkt @ 0xd3614
// size: 228 bytes
//

void qm_leave_queue_pkt(int param_1,int *param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  
  uVar6 = *(undefined4 *)(param_1 + 8);
  _raw_spin_lock_bh(param_3);
  piVar2 = (int *)0x0;
  piVar3 = (int *)0x0;
LAB_000d363c:
  do {
    piVar5 = piVar2;
    piVar2 = (int *)*param_2;
    piVar1 = piVar3;
    while( true ) {
      piVar3 = piVar2;
      if (piVar3 == (int *)0x0) {
        while (piVar5 != (int *)0x0) {
          piVar3 = (int *)*piVar5;
          *piVar5 = 0;
          if ((undefined4 *)param_2[1] == (undefined4 *)0x0) {
            *param_2 = (int)piVar5;
          }
          else {
            *(undefined4 *)param_2[1] = piVar5;
          }
          param_2[1] = (int)piVar5;
          param_2[2] = param_2[2] + 1;
          piVar5 = piVar3;
        }
        _raw_spin_unlock_bh(param_3);
        return;
      }
      iVar4 = *piVar3;
      *piVar3 = 0;
      *param_2 = iVar4;
      if (iVar4 == 0) {
        param_2[1] = 0;
      }
      param_2[2] = param_2[2] + -1;
      if ((int)*(char *)((int)piVar3 + 0x2d) == (uint)*(byte *)(param_1 + 0xc)) break;
      *piVar3 = 0;
      piVar2 = piVar3;
      if (piVar1 == (int *)0x0) goto LAB_000d363c;
      *piVar1 = (int)piVar3;
      piVar2 = (int *)*param_2;
      piVar1 = piVar3;
    }
    RTMPFreeNdisPacket(uVar6);
    piVar2 = piVar5;
    piVar3 = piVar1;
  } while( true );
}

