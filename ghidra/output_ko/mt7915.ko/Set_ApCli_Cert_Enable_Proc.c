// module: mt7915.ko
// function: Set_ApCli_Cert_Enable_Proc @ 0x2a74c
// size: 144 bytes
//

undefined4
Set_ApCli_Cert_Enable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  bool bVar4;
  
  iVar1 = *param_1;
  if (*(int *)(iVar1 + 0x38) != 0x400) {
    return 0;
  }
  uVar3 = *(uint *)(iVar1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,0x10,iVar1,param_4);
  bVar4 = iVar1 != 0;
  piVar2 = param_1;
  if (bVar4) {
    piVar2 = param_1 + 0x1e4000;
  }
  *(bool *)(param_1 + 0x29f315) = bVar4;
  if (bVar4) {
    *(undefined1 *)((int)piVar2 + 0x5071) = 0;
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("I/F(apcli%d) Set_ApCli_Cert_Enable_Proc::(enable = %d)\n",uVar3 & 0xff);
  return 1;
}

