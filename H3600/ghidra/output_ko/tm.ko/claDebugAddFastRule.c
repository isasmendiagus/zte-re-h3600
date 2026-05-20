// module: tm.ko
// function: claDebugAddFastRule @ 0x78200
// size: 640 bytes
//

int claDebugAddFastRule(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined1 local_1e4 [4];
  undefined1 local_1e0 [4];
  undefined1 local_1dc [4];
  undefined1 local_1d8 [4];
  undefined1 auStack_1d4 [20];
  undefined4 local_1c0;
  undefined1 auStack_1bc [4];
  undefined1 auStack_1b8 [4];
  undefined1 auStack_1b4 [4];
  undefined1 auStack_1b0 [4];
  undefined1 auStack_1ac [4];
  undefined4 local_1a8;
  undefined1 auStack_1a4 [4];
  undefined1 auStack_1a0 [4];
  undefined1 auStack_19c [4];
  undefined1 auStack_198 [4];
  undefined1 auStack_194 [4];
  undefined1 local_190 [4];
  uint local_18c;
  uint local_17c;
  undefined2 local_16c;
  undefined2 local_16a;
  undefined2 local_162;
  undefined2 local_160;
  undefined2 local_15e;
  undefined1 local_15a [6];
  undefined1 local_154 [8];
  uint local_14c;
  undefined2 local_13c;
  uint local_138;
  undefined1 local_f4;
  int local_f0;
  undefined1 local_ec [4];
  undefined1 local_e8 [196];
  
  __memzero(auStack_1d4,0x14);
  __memzero(local_190,0xa0);
  sscanf(param_1,"%d %d %d                      %x %x %x %x %x %x %x %x %x %x %x %x %x %x %d %d",
         &local_f0,local_ec,local_e8,&local_1c0,auStack_1bc,auStack_1b8,auStack_1b4,auStack_1b0,
         auStack_1ac,&local_1a8,auStack_1a4,auStack_1a0,auStack_19c,auStack_198,auStack_194,
         local_1e4,local_1dc,local_1e0,local_1d8);
  iVar2 = 0;
  local_160 = 0xffff;
  local_15e = 0x159;
  local_162 = 0;
  local_16c = 0x400;
  local_16a = 0x400;
  local_13c = 0x400;
  local_f4 = 0;
  local_190[0] = (undefined1)local_f0;
  if (local_f0 == 0) {
    uVar11 = 10;
    iVar2 = 0xb;
    iVar10 = 0xb;
    iVar5 = 10;
    iVar3 = 10;
    iVar9 = 10;
    uVar4 = 10;
    iVar1 = 0x14;
    uVar8 = 0xc0;
    iVar7 = 0xa8;
    iVar6 = 1;
  }
  else if (local_f0 == 1) {
    iVar2 = 10;
    uVar4 = 10;
    iVar1 = 10;
    uVar8 = 10;
    iVar7 = 10;
    iVar6 = 10;
    uVar11 = 0xc0;
    iVar5 = 0xa8;
    iVar9 = 0xb;
    iVar10 = 0x14;
    iVar3 = 1;
  }
  else {
    uVar11 = 0;
    iVar5 = 0;
    iVar3 = 0;
    iVar9 = 0;
    uVar4 = 0;
    iVar1 = 0;
    uVar8 = 0;
    iVar7 = 0;
    iVar6 = 0;
    iVar10 = 0;
  }
  local_138 = iVar6 << 0x10 | iVar7 << 8 | uVar8 | iVar2 << 0x18;
  local_18c = iVar6 << 0x10 | iVar10 << 0x18 | uVar8 | iVar7 << 8;
  local_14c = iVar3 << 0x10 | iVar9 << 0x18 | uVar11 | iVar5 << 8;
  local_17c = uVar4 << 0x10 | iVar1 << 0x18 | uVar4 | uVar4 << 8;
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    local_15a[iVar2] = (char)(&local_1c0)[iVar2];
    iVar2 = iVar3;
  } while (iVar3 != 6);
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    local_154[iVar2] = (char)*(undefined4 *)(auStack_1a4 + iVar2 * 4 + -4);
    iVar2 = iVar3;
  } while (iVar3 != 6);
  iVar2 = zte_api_fast_l3_session_add(local_190,auStack_1d4);
  if (iVar2 != 0) {
    printk("[tmtst]addfastrule fail, error code %d!\n",iVar2);
  }
  return iVar2;
}

