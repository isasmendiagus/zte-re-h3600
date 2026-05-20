// module: mt7915.ko
// function: Set_APSDAC_Proc @ 0x57fd8
// size: 308 bytes
//

int Set_APSDAC_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte local_14 [4];
  
  uVar4 = 0;
  local_14[0] = 0;
  local_14[1] = 0;
  local_14[2] = 0;
  local_14[3] = 0;
  iVar3 = rstrtok(param_2,&_LC11);
  if (iVar3 != 0) {
    do {
      bVar2 = os_str_tol(iVar3,0,10);
      local_14[uVar4] = bVar2;
      if (2 < DebugLevel) {
        printk("APSDAC[%d]=%d\n",uVar4,bVar2);
      }
      iVar3 = rstrtok(0,&_LC11);
      iVar1 = DebugLevel;
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < 4 && iVar3 != 0);
    if (uVar4 == 4) {
      if (DebugLevel < 3) {
        iVar3 = 1;
      }
      *(byte *)(param_1 + 0x794ca7) = local_14[0];
      *(byte *)(param_1 + 0x794cc0) = local_14[0];
      *(byte *)(param_1 + 0x794ca8) = local_14[1];
      *(byte *)(param_1 + 0x794cc1) = local_14[1];
      *(byte *)(param_1 + 0x794ca9) = local_14[2];
      *(byte *)(param_1 + 0x794cc2) = local_14[2];
      *(byte *)(param_1 + 0x794caa) = local_14[3];
      *(byte *)(param_1 + 0x794cc3) = local_14[3];
      if (iVar1 < 3) {
        return iVar3;
      }
      printk("APSDAC::(BE,BK,VI,VO)=(%d,%d,%d,%d)\n");
      return 1;
    }
  }
  if (2 < DebugLevel) {
    printk("Invalid parameters\n");
  }
  return 0;
}

