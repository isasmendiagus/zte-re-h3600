// module: mt7915.ko
// function: mt_notify_chain_unregister @ 0x105b28
// size: 108 bytes
//

undefined4 mt_notify_chain_unregister(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  OS_SPIN_LOCK();
  iVar3 = *(int *)(param_1 + 4);
  iVar2 = param_1;
  do {
    iVar1 = iVar3;
    if (iVar1 == 0) {
      uVar4 = 0xffffffff;
LAB_00105b70:
      OS_SPIN_UNLOCK(param_1);
      return uVar4;
    }
    if (param_2 == iVar1) {
      uVar4 = 0;
      *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_2 + 4);
      goto LAB_00105b70;
    }
    iVar3 = *(int *)(iVar1 + 4);
    iVar2 = iVar1;
  } while( true );
}

