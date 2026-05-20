// module: mt7915.ko
// function: Show_PSTable_Proc @ 0xe0904
// size: 244 bytes
//

undefined4 Show_PSTable_Proc(int param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  puVar1 = (undefined4 *)hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (-1 < DebugLevel) {
    pcVar3 = "";
    if (param_2 != (char *)0x0) {
      pcVar3 = param_2;
    }
    printk("%s(): arg=%s\n","Show_PSTable_Proc",pcVar3);
  }
  if (((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
     (iVar2 = rtstrcasecmp(param_2,&_LC463), iVar2 == 1)) {
    uVar4 = 0x20001;
  }
  else {
    iVar2 = rtstrcasecmp(param_2,&_LC464);
    if (iVar2 == 1) {
      uVar4 = 2;
    }
    else {
      uVar4 = 0;
    }
  }
  if (0 < DebugLevel) {
    printk("Dump MacTable entries info, EntType=0x%x\n",uVar4);
  }
  if ((code *)*puVar1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e097c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar4 = (*(code *)*puVar1)(*(undefined4 *)(param_1 + 0xa797a0),uVar4,0);
    return uVar4;
  }
  return 0;
}

