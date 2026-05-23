// module: mt7915.ko
// function: Set_DfsZeroWaitNOP_Proc @ 0x237d5c
// size: 296 bytes
//

undefined4 Set_DfsZeroWaitNOP_Proc(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  
  if (0 < DebugLevel) {
    printk("[%s]\n","Set_DfsZeroWaitNOP_Proc");
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
LAB_00237ddc:
        uVar1 = simple_strtol(iVar4,0,10);
        iVar4 = rstrtok(0,&_LC79);
        if (iVar4 == 0) break;
LAB_00237e04:
        uVar3 = simple_strtol(iVar4,0,10);
        iVar5 = 2;
      }
      else {
        if (iVar5 == 2) goto LAB_00237e04;
        if (iVar5 == 0) {
          uVar2 = simple_strtol(iVar4,0,10);
          iVar4 = rstrtok(0,&_LC79);
          if (iVar4 != 0) goto LAB_00237ddc;
          break;
        }
      }
      iVar5 = iVar5 + 1;
      iVar4 = rstrtok(0,&_LC79);
    } while (iVar4 != 0);
  }
  ZeroWait_DFS_set_NOP_to_Channel_List(param_1,uVar2,uVar1,uVar3);
  return 1;
}

