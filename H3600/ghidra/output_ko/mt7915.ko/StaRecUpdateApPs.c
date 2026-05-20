// module: mt7915.ko
// function: StaRecUpdateApPs @ 0x1c20fc
// size: 220 bytes
//

undefined4 StaRecUpdateApPs(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  undefined2 local_24;
  undefined2 local_22;
  uint local_20;
  undefined4 local_1c;
  
  uVar7 = 0;
  iVar6 = *(int *)(param_3 + 0x9c);
  local_1c = 0;
  if (iVar6 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    uVar4 = 0;
    uVar5 = 0;
    local_24 = 0xb;
    local_22 = 0xc;
    pcVar8 = (char *)(iVar6 + 0xb0c);
    do {
      uVar1 = uVar7 & 0xff;
      uVar2 = uVar7 & 0xff;
      uVar7 = uVar7 + 1;
      if (pcVar8[1] != '\0') {
        uVar5 = uVar5 | 1 << uVar1 & 0xffU;
      }
      if (pcVar8[5] != '\0') {
        uVar4 = uVar4 | 1 << uVar2 & 0xffU;
      }
      pcVar8 = pcVar8 + 1;
    } while (uVar7 != 4);
    local_20 = (uint)CONCAT21(CONCAT11(*(undefined1 *)(iVar6 + 0xb15),(char)uVar5),(char)uVar4);
    if (3 < DebugLevel) {
      printk("%s(STA_REC_AP_PS), Delv=%x Trig=%x SP=%d LInt=%d","StaRecUpdateApPs",uVar4,uVar5,
             *(undefined1 *)(iVar6 + 0xb15),0);
    }
    AndesAppendCmdMsg(param_2,&local_24,0xc);
    uVar3 = 0;
  }
  return uVar3;
}

