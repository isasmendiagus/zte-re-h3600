// module: mt7915.ko
// function: ChannelQualityDetection @ 0x22eec4
// size: 744 bytes
//

void ChannelQualityDetection(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  uint local_24 [2];
  
  iVar5 = *(int *)(param_1 + 0xa7c320);
  iVar4 = *(int *)(param_1 + 0xa7c328);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12250,&local_50);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12254,&local_4c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12258,&local_48);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x1225c,&local_44);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12260,&local_40);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12264,&local_3c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12268,&local_38);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x1226c,&local_34);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12270,&local_30);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12274,&local_2c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12278,&local_28);
  uVar3 = local_4c + local_50 + local_48 + local_44 + local_40 + local_3c + local_38 + local_34 +
          local_30 + local_2c + local_28;
  if (uVar3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = __aeabi_uidiv((local_28 + local_2c) * 100,uVar3);
  }
  *(uint *)(param_1 + 0xa7961c) = uVar1;
  *(uint *)(param_1 + 0xa79794) = uVar3;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x12230,local_24);
  local_24[0] = local_24[0] | 0x20000000;
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x12230);
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x12230,local_24[0]);
  iVar2 = *(int *)(param_1 + 0xa79184);
  if (iVar2 != 1) {
    if (((*(char *)(param_1 + 0xa79753) == '\0') || (uVar1 <= *(byte *)(param_1 + 0xa79620))) ||
       (uVar3 <= *(uint *)(param_1 + 0xa79798))) {
      if (iVar2 != 4) {
        return;
      }
      uVar3 = *(int *)(param_1 + 0xa79614) + 1;
      *(uint *)(param_1 + 0xa79614) = uVar3;
      if (uVar3 < *(uint *)(param_1 + 0xa79610)) {
        return;
      }
      if (99999 < (uint)(iVar4 + iVar5)) {
        return;
      }
      *(undefined4 *)(param_1 + 0xa79614) = 0;
      uVar6 = 1;
    }
    else if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0xa79754) = 2;
      *(undefined1 *)(param_1 + 0xa79791) = 1;
      uVar6 = 2;
    }
    else {
      if (iVar2 != 4) {
        return;
      }
      *(undefined4 *)(param_1 + 0xa79614) = 0;
      *(undefined1 *)(param_1 + 0xa79754) = 2;
      *(undefined1 *)(param_1 + 0xa79791) = 1;
      MlmeEnqueue(param_1,0x2b,2,0,0,0);
      uVar6 = 2;
    }
    MlmeEnqueue(param_1,0x2b,0,0,0,uVar6);
    RtmpOsMlmeUp(param_1 + 0x286298);
  }
  return;
}

