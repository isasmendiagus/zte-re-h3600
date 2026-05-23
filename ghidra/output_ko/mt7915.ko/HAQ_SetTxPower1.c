// module: mt7915.ko
// function: HAQ_SetTxPower1 @ 0x26fa08
// size: 208 bytes
//

int HAQ_SetTxPower1(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  code *pcVar3;
  undefined4 local_34;
  int local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HAQ_SetTxPower1");
  }
  uVar1 = *(ushort *)(param_3 + 0xc);
  os_zero_mem(&local_34,0x14);
  pcVar3 = *(code **)(iVar2 + 0x30);
  local_30 = (int)(short)(uVar1 << 8 | uVar1 >> 8);
  iVar2 = local_30;
  if (pcVar3 == (code *)0x0) {
    iVar2 = 1;
  }
  local_28 = 0;
  if (pcVar3 != (code *)0x0) {
    iVar2 = (*pcVar3)(param_1,local_34,local_30,uStack_2c,0,uStack_24);
  }
  FUN_0026cdd0(param_3,param_2,2,iVar2);
  return iVar2;
}

