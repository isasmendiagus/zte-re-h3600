// module: mt7915.ko
// function: Set_RADIUS_Port_Proc @ 0x2b134
// size: 268 bytes
//

undefined4 Set_RADIUS_Port_Proc(int *param_1,undefined4 param_2)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  
  uVar6 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar6) {
    return 0;
  }
  iVar4 = rstrtok(param_2,&_LC132);
  if (iVar4 != 0) {
    iVar7 = 0;
    bVar2 = 0;
    do {
      if (iVar7 < (int)(uint)*(byte *)(param_1 + uVar6 * 0x160d + 0xadddb)) {
        uVar5 = os_str_tol(iVar4,0,10);
        iVar3 = DebugLevel;
        iVar4 = iVar7 * 0x49;
        iVar7 = iVar7 + 1;
        *(undefined4 *)((int)param_1 + (int)("Ac1 --> %uus(%u)\n" + iVar4 + uVar6 * 0x5834 + 0x11))
             = uVar5;
        if (2 < iVar3) {
          printk("IF(ra%d), radius_port(seq-%d)=%d\n",uVar6,iVar7);
        }
      }
      iVar4 = rstrtok(0,&_LC132);
      bVar1 = (bool)(bVar2 ^ 1);
      bVar2 = 1;
      if (iVar4 == 0) {
        bVar1 = false;
      }
    } while (bVar1);
  }
  return 1;
}

