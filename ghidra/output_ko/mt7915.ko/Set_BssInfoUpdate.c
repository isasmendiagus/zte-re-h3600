// module: mt7915.ko
// function: Set_BssInfoUpdate @ 0xe6a90
// size: 372 bytes
//

bool Set_BssInfoUpdate(int param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  bool bVar4;
  size_t sVar5;
  byte *__s;
  int iVar6;
  undefined4 *puVar7;
  undefined1 local_142;
  undefined1 local_141;
  undefined1 local_140;
  undefined1 local_13f;
  undefined1 local_13e;
  undefined1 local_13d;
  undefined4 local_13c;
  undefined4 local_138;
  undefined1 auStack_134 [4];
  undefined4 local_130;
  undefined1 local_128;
  undefined1 local_127;
  undefined1 auStack_126 [6];
  undefined2 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined1 local_114;
  undefined4 local_f8;
  undefined1 local_2e;
  
  local_13c = 0;
  local_138 = 0;
  uVar1 = *(undefined1 *)(*(int *)(param_1 + 0xa77bb8) + 0x4cc);
  sVar5 = strlen(param_2);
  if (sVar5 == 0x17) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      puVar7 = &local_13c;
      do {
        sVar5 = strlen((char *)__s);
        if (((sVar5 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_000e6acc;
        AtoH(__s,puVar7);
        __s = (byte *)rstrtok(0,&_LC232);
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      } while (__s != (byte *)0x0);
    }
    local_140 = (undefined1)local_138;
    local_13f = local_138._1_1_;
    local_13d = local_138._3_1_;
    uVar2 = (undefined1)local_13c;
    uVar3 = local_13c._1_1_;
    local_13e = local_138._2_1_;
    local_142 = local_13c._2_1_;
    local_141 = local_13c._3_1_;
    __memzero(auStack_134,0x114);
    local_128 = uVar2;
    local_127 = uVar3;
    os_move_mem(auStack_126,&local_142,6);
    local_120 = 1;
    local_118 = 0x10002;
    local_11c = 0x10000;
    local_114 = 0;
    local_130 = 2;
    local_f8 = 3;
    local_2e = uVar1;
    iVar6 = AsicBssInfoUpdate(param_1,auStack_134);
    bVar4 = iVar6 == 0;
  }
  else {
LAB_000e6acc:
    bVar4 = false;
  }
  return bVar4;
}

