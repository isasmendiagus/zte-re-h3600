// module: mt7915.ko
// function: vht_prim_ch_idx @ 0x20263c
// size: 356 bytes
//

undefined4 vht_prim_ch_idx(uint param_1,uint param_2,int param_3)

{
  byte *pbVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (param_1 != param_2) {
    if (param_3 == 8) {
      uVar2 = (uint)DAT_005dfe49;
      if (uVar2 == 0) goto LAB_002026cc;
      if (DAT_005dfe4a == param_1) {
        iVar4 = 0;
      }
      else {
        iVar4 = 0;
        puVar3 = &_LANCHOR1;
        do {
          uVar2 = (uint)(byte)puVar3[4];
          iVar4 = iVar4 + 1;
          if (uVar2 == 0) goto LAB_002026cc;
          pbVar1 = puVar3 + 5;
          puVar3 = puVar3 + 3;
        } while (*pbVar1 != param_1);
      }
      if (param_2 != uVar2) {
        if ((byte)(&_LANCHOR1)[iVar4 * 3] == param_2) goto LAB_0020265c;
LAB_00202738:
        if (param_1 < param_2) {
          uVar5 = 2;
        }
        else {
          uVar5 = 1;
        }
        goto LAB_00202660;
      }
LAB_00202748:
      uVar5 = 3;
      goto LAB_00202660;
    }
    if (param_3 == 0x20) {
      uVar2 = (uint)DAT_005dfe61;
      if (uVar2 == 0) {
LAB_002026cc:
        uVar5 = 0;
        goto LAB_00202660;
      }
      if (DAT_005dfe62 == param_1) {
        iVar4 = 0;
      }
      else {
        uVar2 = (uint)DAT_005dfe64;
        if (uVar2 == 0) goto LAB_002026cc;
        if (DAT_005dfe65 == param_1) {
          iVar4 = 1;
        }
        else {
          uVar2 = (uint)DAT_005dfe67;
          if (uVar2 == 0) goto LAB_002026cc;
          iVar4 = 2;
        }
      }
      if (param_2 == uVar2) goto LAB_00202748;
      if ((byte)(&DAT_005dfe60)[iVar4 * 3] != param_2) goto LAB_00202738;
    }
  }
LAB_0020265c:
  uVar5 = 0;
LAB_00202660:
  if (3 < DebugLevel) {
    printk("%s():(VhtCentCh=%d, PrimCh=%d) =>BbpChIdx=%d\n","vht_prim_ch_idx",param_1,param_2,uVar5)
    ;
  }
  return uVar5;
}

