// module: mt7915.ko
// function: Set_StaRecCmmUpdate @ 0xe6898
// size: 504 bytes
//

bool Set_StaRecCmmUpdate(int param_1,char *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  size_t sVar3;
  byte *__s;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  undefined1 auStack_1d8 [200];
  uint local_110;
  uint local_10c;
  byte local_105;
  undefined1 local_104;
  byte local_103;
  undefined1 local_102;
  undefined1 local_101;
  byte local_100;
  byte local_ff;
  undefined1 local_fe;
  undefined1 local_fd;
  uint local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined1 local_ec;
  int local_60;
  
  local_105 = 0;
  local_104 = 0;
  local_103 = 0;
  local_102 = 0;
  local_101 = 0;
  local_100 = 0;
  local_ff = 0;
  local_fe = 0;
  local_fd = 0;
  sVar3 = strlen(param_2);
  if (sVar3 == 0x1a) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      pbVar6 = &local_105;
      do {
        sVar3 = strlen((char *)__s);
        if (sVar3 != 2) {
          return false;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return false;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return false;
        }
        AtoH(__s,pbVar6);
        __s = (byte *)rstrtok(0,&_LC232);
        pbVar6 = pbVar6 + 1;
      } while (__s != (byte *)0x0);
    }
    uVar2 = local_104;
    bVar1 = local_105;
    iVar5 = param_1 + (uint)local_105 * 0x14c0 + 0xa1d20;
    if (iVar5 != 0) {
      local_110 = (uint)local_100;
      iVar4 = param_1 + (uint)local_105 * 0x14c0;
      *(ushort *)(iVar4 + 0xa1e18) = (ushort)local_103;
      *(undefined1 *)(iVar4 + 0xa1e0c) = local_102;
      *(undefined1 *)(iVar4 + 0xa1e0d) = local_101;
      local_10c = (uint)local_ff;
      *(byte *)(iVar4 + 0xa1e0e) = local_100;
      *(byte *)(iVar4 + 0xa1e0f) = local_ff;
      *(undefined1 *)(iVar4 + 0xa1e10) = local_fe;
      *(undefined1 *)(iVar4 + 0xa1e11) = local_fd;
      os_zero_mem(&local_fc,0xd4);
      local_f4 = 0x10002;
      local_f0 = 1;
      local_ec = 1;
      local_f8 = CONCAT22(local_f8._2_2_,1);
      local_fc = CONCAT31(local_fc._1_3_,uVar2);
      local_fc = (uint)CONCAT12(bVar1,(undefined2)local_fc);
      local_60 = iVar5;
      memcpy(auStack_1d8,&local_f0,200);
      iVar5 = CmdExtStaRecUpdate(param_1,local_fc,local_f8,local_f4);
      return iVar5 == 0;
    }
  }
  return false;
}

