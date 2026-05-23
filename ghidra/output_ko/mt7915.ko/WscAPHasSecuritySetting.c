// module: mt7915.ko
// function: WscAPHasSecuritySetting @ 0x1ecf8c
// size: 196 bytes
//

undefined4
WscAPHasSecuritySetting(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  uint extraout_r2;
  int iVar3;
  int extraout_r3;
  undefined4 uVar4;
  
  bVar1 = *(byte *)(param_2 + 0x1c94);
  uVar2 = (uint)*(ushort *)(param_2 + (uint)bVar1 * 0x74 + 0x1cbe);
  switch(uVar2) {
  case 1:
    uVar4 = 0;
    break;
  case 2:
  case 4:
  case 8:
  case 0xc:
    uVar4 = 1;
    break;
  default:
    iVar3 = DebugLevel;
    if (2 < DebugLevel) {
      printk("%s: Incorrect encryption types (%d)\n","WscAPHasSecuritySetting",uVar2,DebugLevel,
             param_4);
      uVar2 = extraout_r2;
      iVar3 = extraout_r3;
    }
    uVar4 = 0;
    printk(&_LC269,0x32d5,uVar2,iVar3,param_4);
    dump_stack();
  }
  if (2 < DebugLevel) {
    param_2 = (uint)bVar1 * 0x74 + param_2;
    printk("%s: WSC Entryption Type = %d\n","WscAPHasSecuritySetting",
           *(undefined2 *)(param_2 + 0x1cbe),param_2 + 0x1c80,param_4);
  }
  return uVar4;
}

