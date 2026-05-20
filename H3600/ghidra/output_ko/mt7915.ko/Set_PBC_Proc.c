// module: mt7915.ko
// function: Set_PBC_Proc @ 0xc3328
// size: 188 bytes
//

undefined4 Set_PBC_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if (0 < DebugLevel) {
    printk("Set PBC Up bound:\n");
  }
  iVar2 = rstrtok(param_2,&_LC156);
  if (iVar2 != 0) {
    uVar4 = 0;
    do {
      uVar1 = os_str_tol(iVar2,0,10);
      iVar2 = DebugLevel;
      uVar5 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      iVar3 = param_1 + (uVar5 + 0x53e2a0) * 2;
      *(undefined2 *)(iVar3 + 6) = uVar1;
      if (0 < iVar2) {
        printk("%d: %d\n",uVar5,uVar1,iVar3,param_4);
      }
      iVar2 = rstrtok(0,&_LC156);
    } while (iVar2 != 0);
  }
  return 1;
}

