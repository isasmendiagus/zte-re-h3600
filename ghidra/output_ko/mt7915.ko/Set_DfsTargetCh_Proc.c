// module: mt7915.ko
// function: Set_DfsTargetCh_Proc @ 0x231ae8
// size: 300 bytes
//

undefined4 Set_DfsTargetCh_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  
  if (0 < DebugLevel) {
    printk("[%s]\n","Set_DfsTargetCh_Proc");
  }
  iVar4 = rstrtok(param_2,&_LC79);
  if (iVar4 == 0) {
    uVar3 = 0;
    uVar1 = 0;
    uVar2 = 0;
  }
  else {
    uVar3 = 0;
    uVar1 = 0;
    uVar2 = 0;
    iVar5 = 0;
    do {
      if (iVar5 == 1) {
LAB_00231b68:
        uVar1 = simple_strtol(iVar4,0,10);
        iVar4 = rstrtok(0,&_LC79);
        if (iVar4 == 0) break;
LAB_00231b90:
        uVar3 = simple_strtol(iVar4,0,10);
        iVar5 = 2;
      }
      else {
        if (iVar5 == 2) goto LAB_00231b90;
        if (iVar5 == 0) {
          uVar2 = simple_strtol(iVar4,0,10);
          iVar4 = rstrtok(0,&_LC79);
          if (iVar4 != 0) goto LAB_00231b68;
          break;
        }
      }
      iVar5 = iVar5 + 1;
      iVar4 = rstrtok(0,&_LC79);
    } while (iVar4 != 0);
  }
  *(undefined1 *)(param_1 + 0x7953f1) = uVar2;
  *(undefined1 *)(param_1 + 0x7953f2) = uVar1;
  *(undefined2 *)(param_1 + 0x7953f4) = uVar3;
  return 1;
}

