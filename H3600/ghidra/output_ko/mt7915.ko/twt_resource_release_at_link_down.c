// module: mt7915.ko
// function: twt_resource_release_at_link_down @ 0x167864
// size: 148 bytes
//

void twt_resource_release_at_link_down
               (int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  if (param_1 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: wdev=NULL, please check\n","twt_resource_release_at_link_down",param_3,param_4);
    return;
  }
  iVar5 = param_2 * 0x14c0 + *(int *)(param_1 + 8);
  uVar3 = (uint)*(byte *)(iVar5 + 0xa3185);
  if (uVar3 == 0) {
    return;
  }
  uVar4 = 0;
  while( true ) {
    uVar1 = uVar4 & 0xff;
    uVar2 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    if (((int)uVar3 >> uVar1 & 1U) != 0) {
      FUN_00167230(param_1,param_2,uVar2);
    }
    if (uVar4 == 8) break;
    uVar3 = (uint)*(byte *)(iVar5 + 0xa3185);
  }
  return;
}

