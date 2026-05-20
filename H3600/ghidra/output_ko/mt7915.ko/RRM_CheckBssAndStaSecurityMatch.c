// module: mt7915.ko
// function: RRM_CheckBssAndStaSecurityMatch @ 0x21dd78
// size: 196 bytes
//

undefined4 RRM_CheckBssAndStaSecurityMatch(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar5 = 0;
  if ((*(uint *)(param_3 + 0xc4) & *(uint *)(param_2 + 0x17c)) != 0) {
    if ((*(uint *)(param_2 + 0x2c4) & *(uint *)(param_3 + 200)) == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 1;
    }
  }
  if (2 < DebugLevel) {
    uVar1 = GetAuthModeStr();
    uVar2 = GetEncryModeStr(*(undefined4 *)(param_3 + 200));
    uVar3 = GetAuthModeStr(*(undefined4 *)(param_2 + 0x17c));
    uVar4 = GetEncryModeStr(*(undefined4 *)(param_2 + 0x2c4));
    printk("%s: pBssEntry %s/%s & pSTA %s/%s = (%d/%d)  ret %d\n","RRM_CheckBssAndStaSecurityMatch",
           uVar1,uVar2,uVar3,uVar4,*(uint *)(param_2 + 0x17c) & *(uint *)(param_3 + 0xc4),
           *(uint *)(param_3 + 200) & *(uint *)(param_2 + 0x2c4),uVar5);
  }
  return uVar5;
}

