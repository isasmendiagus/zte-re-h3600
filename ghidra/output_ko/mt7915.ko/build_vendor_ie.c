// module: mt7915.ko
// function: build_vendor_ie @ 0x1464cc
// size: 608 bytes
//

int build_vendor_ie(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  size_t *psVar3;
  uint uVar4;
  int iVar5;
  int local_178;
  int local_174;
  int local_170;
  int local_16c;
  undefined4 local_166;
  undefined1 local_162;
  undefined4 local_161;
  undefined2 local_15d;
  undefined1 local_15b;
  undefined1 local_15a;
  undefined1 local_159;
  undefined1 local_158;
  undefined1 local_157;
  undefined1 local_156;
  byte local_155;
  undefined4 local_151;
  undefined4 local_14d;
  undefined4 local_149;
  undefined2 local_145;
  undefined4 local_143;
  undefined4 local_13f;
  undefined4 local_13b;
  undefined2 local_137;
  undefined4 local_135;
  undefined2 local_131;
  undefined1 local_12f;
  undefined4 local_12e;
  undefined1 local_12a;
  undefined1 local_129;
  undefined1 local_128;
  undefined1 auStack_127 [259];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = 0;
  local_161 = 0x5c0;
  local_166 = 0x20103c3;
  local_15d = 0x2a00;
  local_15b = 0xff;
  local_151 = 0x1b10cbf;
  local_162 = 2;
  local_14d = 0xff2a33c0;
  local_149 = 0xff2a0492;
  local_145 = 0x492;
  local_178 = 0;
  local_170 = 0;
  local_16c = 0;
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 == 2) {
    __memzero(&local_15a,9);
    __memzero(&local_143,0x1a);
    local_13f = local_14d;
    local_13b = local_149;
    local_143 = local_151;
    local_135 = local_161;
    local_131 = local_15d;
    local_12f = local_15b;
    local_158 = 0;
    local_137 = local_145;
    local_12e = local_166;
    local_12a = local_162;
    local_16c = 0x1a;
    local_15a = 0xdd;
    local_159 = 0x21;
    local_157 = 0xc;
    local_156 = 0xe7;
    if (((*(char *)(param_1 + 0x79505f) != '\0') && (*(char *)(iVar1 + 0x6c) != '\0')) &&
       ((*(ushort *)(param_2 + 0x18) & 8) != 0)) {
      local_155 = local_155 | 8;
    }
    if (*(char *)(param_2 + 0x3f59) != '\0') {
      local_155 = ~((byte)~(byte)(((uint)local_155 << 0x19) >> 0x18) >> 1);
    }
    MakeOutgoingFrame(param_3,&local_170,9,&local_15a,0xffffffff);
    iVar5 = local_170;
    MakeOutgoingFrame(param_3 + local_170,&local_16c,0x1a,&local_143,0xffffffff);
    iVar5 = iVar5 + local_16c;
  }
  FUN_0014580c(param_2,&local_178,1 << (param_4 & 0xff));
  if (local_178 != 0) {
    for (psVar3 = *(size_t **)(local_178 + 8); psVar3 != (size_t *)0x0; psVar3 = (size_t *)psVar3[3]
        ) {
      local_174 = 0;
      __memzero(&local_129,0x101);
      local_129 = 0xdd;
      uVar4 = *psVar3;
      local_128 = (undefined1)uVar4;
      memcpy(auStack_127,(void *)psVar3[2],*psVar3);
      MakeOutgoingFrame(param_3 + iVar5,&local_174,(uVar4 & 0xff) + 2,&local_129,0xffffffff);
      iVar5 = iVar5 + local_174;
    }
  }
  return iVar5;
}

