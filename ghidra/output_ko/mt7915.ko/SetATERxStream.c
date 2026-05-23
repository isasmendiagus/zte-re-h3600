// module: mt7915.ko
// function: SetATERxStream @ 0x260ad8
// size: 108 bytes
//

bool SetATERxStream(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = net_ad_wrap_service();
  uVar1 = *(undefined1 *)(iVar2 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: Parm = %s\n","SetATERxStream",param_2);
  }
  uVar3 = simple_strtol(param_2,0,10);
  iVar2 = MtATESetRxPath(param_1,uVar3,uVar1);
  return iVar2 == 0;
}

