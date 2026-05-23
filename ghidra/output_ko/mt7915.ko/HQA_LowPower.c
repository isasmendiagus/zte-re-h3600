// module: mt7915.ko
// function: HQA_LowPower @ 0x2767bc
// size: 180 bytes
//

bool HQA_LowPower(int param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  bool bVar3;
  undefined4 local_20;
  int local_1c [2];
  
  local_1c[0] = param_3 + 0xc;
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  local_20 = 0;
  FUN_00276034(1,4,local_1c,&local_20);
  if (2 < DebugLevel) {
    printk("%s Control:%d\n","HQA_LowPower",local_20);
  }
  pcVar1 = *(code **)(iVar2 + 0x7c);
  bVar3 = pcVar1 == (code *)0x0;
  if (!bVar3) {
    (*pcVar1)(param_1,local_20);
  }
  FUN_0026cdd0(param_3,param_2,2,bVar3);
  return bVar3;
}

