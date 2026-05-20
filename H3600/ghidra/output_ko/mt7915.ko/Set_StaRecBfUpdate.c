// module: mt7915.ko
// function: Set_StaRecBfUpdate @ 0xe5da8
// size: 968 bytes
//

bool Set_StaRecBfUpdate(int param_1,char *param_2)

{
  size_t sVar1;
  byte *__s;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  undefined1 auStack_1e8 [204];
  int local_11c;
  byte local_113;
  undefined1 local_112;
  byte local_111;
  undefined1 local_110;
  undefined1 local_10f;
  undefined1 local_10e;
  undefined1 local_10d;
  undefined1 local_10c;
  undefined1 local_10b;
  undefined1 local_10a;
  undefined1 local_109;
  undefined1 local_108;
  undefined1 local_107;
  undefined1 local_106;
  undefined1 local_105;
  undefined1 local_104;
  byte local_103;
  undefined1 local_102;
  byte local_101;
  undefined1 local_100;
  byte local_ff;
  undefined1 local_fe;
  byte local_fd;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0 [36];
  int local_60;
  
  memset(&local_113,0,0x17);
  sVar1 = strlen(param_2);
  if (sVar1 == 0x44) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      pbVar4 = &local_113;
      do {
        sVar1 = strlen((char *)__s);
        if (sVar1 != 2) {
          return false;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return false;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return false;
        }
        AtoH(__s,pbVar4);
        __s = (byte *)rstrtok(0,&_LC232);
        pbVar4 = pbVar4 + 1;
      } while (__s != (byte *)0x0);
    }
    uVar3 = (uint)local_113;
    local_11c = param_1 + uVar3 * 0x14c0 + 0xa1d20;
    if (local_11c != 0) {
      iVar5 = param_1 + uVar3 * 0x14c0;
      *(ushort *)(iVar5 + 0xa295a) = (ushort)local_111;
      *(undefined1 *)(iVar5 + 0xa295c) = local_110;
      *(undefined1 *)(iVar5 + 0xa295f) = local_10e;
      *(undefined1 *)(iVar5 + 0xa295d) = local_10f;
      *(undefined1 *)(iVar5 + 0xa2961) = local_10c;
      *(undefined1 *)(iVar5 + 0xa2960) = local_10d;
      *(undefined1 *)(iVar5 + 0xa2962) = local_10b;
      *(undefined1 *)(iVar5 + 0xa2963) = local_10a;
      *(undefined1 *)(iVar5 + 0xa2964) = local_109;
      *(byte *)(iVar5 + 0xa2969) = *(byte *)(iVar5 + 0xa2969) & 0xc0 | local_103 & 0x3f;
      *(undefined1 *)(iVar5 + 0xa2965) = local_108;
      *(undefined1 *)(iVar5 + 0xa2972) = local_107;
      *(undefined1 *)(iVar5 + 0xa2966) = local_106;
      *(undefined1 *)(iVar5 + 0xa2967) = local_105;
      *(undefined1 *)(iVar5 + 0xa2968) = local_104;
      *(undefined1 *)(iVar5 + 0xa296a) = local_102;
      *(byte *)(iVar5 + 0xa296b) = *(byte *)(iVar5 + 0xa296b) & 0xc0 | local_101 & 0x3f;
      *(undefined1 *)(iVar5 + 0xa296c) = local_100;
      *(undefined1 *)(iVar5 + 0xa296e) = local_fe;
      *(byte *)(iVar5 + 0xa296d) = *(byte *)(iVar5 + 0xa296d) & 0xc0 | local_ff & 0x3f;
      *(undefined2 *)(iVar5 + 0xa2970) = 0;
      *(byte *)(iVar5 + 0xa296f) = *(byte *)(iVar5 + 0xa296f) & 0xc0 | local_fd & 0x3f;
      *(undefined1 *)(iVar5 + 0xa295e) = 1;
      *(undefined1 *)(iVar5 + 0xa2975) = 0;
      *(undefined1 *)(iVar5 + 0xa2976) = 0;
      *(undefined1 *)(iVar5 + 0xa2977) = 0;
      *(undefined1 *)(iVar5 + 0xa2978) = 0;
      *(undefined1 *)(iVar5 + 0xa2979) = 0;
      *(undefined1 *)(iVar5 + 0xa2974) = 0xff;
      *(undefined1 *)(iVar5 + 0xa297a) = 0;
      *(undefined1 *)(iVar5 + 0xa297b) = 0;
      *(undefined1 *)(iVar5 + 0xa297c) = 0;
      *(undefined1 *)(iVar5 + 0xa297d) = 0;
      *(undefined1 *)(iVar5 + 0xa297e) = 0;
      *(undefined1 *)(iVar5 + 0xa297f) = 0;
      *(undefined1 *)(iVar5 + 0xa2980) = 0;
      *(undefined1 *)(iVar5 + 0xa2981) = 0;
      *(undefined1 *)(iVar5 + 0xa2982) = 0;
      uVar2 = *(uint *)(param_1 + 0xa787b8);
      if ((uVar2 & 1) != 0) {
        *(undefined1 *)(iVar5 + 0xa295c) = *(undefined1 *)(param_1 + 0xa787bc);
      }
      if ((uVar2 & 2) != 0) {
        iVar5 = uVar3 * 0x14c0 + param_1;
        *(undefined1 *)(iVar5 + 0xa297a) = *(undefined1 *)(param_1 + 0xa787bd);
        *(undefined1 *)(iVar5 + 0xa297b) = *(undefined1 *)(param_1 + 0xa787be);
      }
      if ((uVar2 & 4) != 0) {
        iVar5 = uVar3 * 0x14c0 + param_1;
        *(undefined1 *)(iVar5 + 0xa297c) = *(undefined1 *)(param_1 + 0xa787bf);
        *(undefined1 *)(iVar5 + 0xa297d) = *(undefined1 *)(param_1 + 0xa787c0);
      }
      if ((uVar2 & 8) != 0) {
        iVar5 = uVar3 * 0x14c0 + param_1;
        *(undefined1 *)(iVar5 + 0xa297e) = *(undefined1 *)(param_1 + 0xa787c1);
        *(undefined1 *)(iVar5 + 0xa297f) = *(undefined1 *)(param_1 + 0xa787c2);
      }
      if ((uVar2 & 0x10) != 0) {
        iVar5 = uVar3 * 0x14c0 + param_1;
        *(undefined1 *)(iVar5 + 0xa2980) = *(undefined1 *)(param_1 + 0xa787c3);
        *(undefined1 *)(iVar5 + 0xa2981) = *(undefined1 *)(param_1 + 0xa787c4);
      }
      if ((uVar2 & 0x20) != 0) {
        *(undefined1 *)(uVar3 * 0x14c0 + param_1 + 0xa2982) = *(undefined1 *)(param_1 + 0xa787c5);
      }
      if ((uVar2 & 0x40) != 0) {
        iVar5 = uVar3 * 0x14c0 + param_1;
        *(undefined1 *)(iVar5 + 0xa2976) = *(undefined1 *)(param_1 + 0xa787c6);
        *(undefined1 *)(iVar5 + 0xa2977) = *(undefined1 *)(param_1 + 0xa787c7);
      }
      if ((uVar2 & 0x80) != 0) {
        iVar5 = uVar3 * 0x14c0 + param_1;
        *(undefined1 *)(iVar5 + 0xa2978) = *(undefined1 *)(param_1 + 0xa787c8);
        *(undefined1 *)(iVar5 + 0xa2979) = *(undefined1 *)(param_1 + 0xa787c9);
      }
      os_zero_mem(&local_fc,0xd4);
      local_60 = local_11c;
      local_f0[0] = 0x10;
      local_f8 = CONCAT22(local_f8._2_2_,1);
      local_f4 = 0;
      local_fc = CONCAT31(CONCAT12(local_113,(undefined2)local_fc) >> 8,local_112);
      memcpy(auStack_1e8,local_f0,200);
      iVar5 = CmdExtStaRecUpdate(param_1,local_fc,local_f8,local_f4);
      os_zero_mem(param_1 + 0xa787b8,0x14);
      return iVar5 == 0;
    }
  }
  return false;
}

