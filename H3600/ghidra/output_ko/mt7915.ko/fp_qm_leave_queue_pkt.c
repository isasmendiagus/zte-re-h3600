// module: mt7915.ko
// function: fp_qm_leave_queue_pkt @ 0xd50c0
// size: 452 bytes
//

void fp_qm_leave_queue_pkt
               (int param_1,int *param_2,int *param_3,undefined4 param_4,undefined4 param_5)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  
  uVar4 = *(undefined4 *)(param_1 + 8);
  _raw_spin_lock_bh(param_4);
  piVar3 = (int *)0x0;
  piVar1 = (int *)0x0;
LAB_000d50f8:
  do {
    piVar5 = piVar1;
    piVar1 = (int *)*param_2;
    piVar6 = piVar3;
    while( true ) {
      piVar3 = piVar1;
      if (piVar3 == (int *)0x0) goto joined_r0x000d5158;
      iVar2 = *piVar3;
      *piVar3 = 0;
      *param_2 = iVar2;
      if (iVar2 == 0) {
        param_2[1] = 0;
      }
      param_2[2] = param_2[2] + -1;
      if ((int)*(char *)((int)piVar3 + 0x2d) == (uint)*(byte *)(param_1 + 0xc)) break;
      *piVar3 = 0;
      piVar1 = piVar3;
      if (piVar6 == (int *)0x0) goto LAB_000d50f8;
      *piVar6 = (int)piVar3;
      piVar1 = (int *)*param_2;
      piVar6 = piVar3;
    }
    RTMPFreeNdisPacket(uVar4,piVar3);
    piVar3 = piVar6;
    piVar1 = piVar5;
  } while( true );
joined_r0x000d5158:
  while (piVar5 != (int *)0x0) {
    piVar3 = (int *)*piVar5;
    *piVar5 = 0;
    if (piVar3 == (int *)0x0) {
      piVar6 = (int *)0x0;
    }
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
  _raw_spin_lock_bh(param_5);
  piVar3 = (int *)0x0;
LAB_000d51a4:
  do {
    piVar5 = piVar3;
    piVar3 = (int *)*param_3;
    piVar1 = piVar6;
    while( true ) {
      piVar6 = piVar3;
      if (piVar6 == (int *)0x0) {
        while (piVar5 != (int *)0x0) {
          piVar3 = (int *)*piVar5;
          *piVar5 = 0;
          if ((undefined4 *)param_3[1] == (undefined4 *)0x0) {
            *param_3 = (int)piVar5;
          }
          else {
            *(undefined4 *)param_3[1] = piVar5;
          }
          param_3[1] = (int)piVar5;
          param_3[2] = param_3[2] + 1;
          piVar5 = piVar3;
        }
        _raw_spin_unlock_bh(param_5);
        _raw_spin_unlock_bh(param_4);
        return;
      }
      iVar2 = *piVar6;
      *piVar6 = 0;
      *param_3 = iVar2;
      if (iVar2 == 0) {
        param_3[1] = 0;
      }
      param_3[2] = param_3[2] + -1;
      if ((int)*(char *)((int)piVar6 + 0x2d) == (uint)*(byte *)(param_1 + 0xc)) break;
      *piVar6 = 0;
      piVar3 = piVar6;
      if (piVar1 == (int *)0x0) goto LAB_000d51a4;
      *piVar1 = (int)piVar6;
      piVar3 = (int *)*param_3;
      piVar1 = piVar6;
    }
    RTMPFreeNdisPacket(uVar4);
    piVar3 = piVar5;
    piVar6 = piVar1;
  } while( true );
}

