// module: mt7915.ko
// function: Set_DedicatedBwCh_Proc @ 0x236cc8
// size: 408 bytes
//

undefined4 Set_DedicatedBwCh_Proc(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  
  if (0 < DebugLevel) {
    printk("[%s]\n","Set_DedicatedBwCh_Proc");
  }
  iVar5 = rstrtok(param_2,&_LC79);
  if (iVar5 == 0) {
    uVar4 = 1;
    *(undefined1 *)(param_1 + 0x795404) = 0;
    uVar3 = 0;
    bVar1 = 0;
    uVar2 = 0;
  }
  else {
    uVar3 = 0;
    uVar4 = 1;
    uVar2 = 0;
    bVar1 = 0;
    iVar6 = 0;
    do {
      switch(iVar6) {
      case 0:
        bVar1 = simple_strtol(iVar5,0,10);
        iVar5 = rstrtok(0,&_LC79);
        if (iVar5 == 0) goto LAB_00236ddc;
        break;
      case 1:
        break;
      case 2:
        goto switchD_00236d1c_caseD_2;
      case 3:
        goto switchD_00236d1c_caseD_3;
      default:
        goto switchD_00236d1c_default;
      }
      uVar2 = simple_strtol(iVar5,0,10);
      iVar5 = rstrtok(0,&_LC79);
      if (iVar5 == 0) break;
switchD_00236d1c_caseD_2:
      uVar3 = simple_strtol(iVar5,0,10);
      iVar5 = rstrtok(0,&_LC79);
      if (iVar5 == 0) break;
switchD_00236d1c_caseD_3:
      uVar4 = simple_strtol(iVar5,0,10);
      iVar6 = 3;
switchD_00236d1c_default:
      iVar6 = iVar6 + 1;
      iVar5 = rstrtok(0,&_LC79);
    } while (iVar5 != 0);
LAB_00236ddc:
    *(undefined1 *)(param_1 + 0x795404) = 0;
    if (1 < bVar1) {
      if (bVar1 == 2) {
        DfsDedicatedOutBandSetChannel(param_1,uVar2,uVar3,2);
      }
      return 1;
    }
  }
  DfsDedicatedInBandSetChannel(param_1,uVar2,uVar3,uVar4,bVar1);
  return 1;
}

