// module: mt7915.ko
// function: MtAsicUpdateBASessionByFw @ 0x198960
// size: 408 bytes
//

undefined4
MtAsicUpdateBASessionByFw
          (int param_1,uint param_2,uint param_3,int param_4,undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  byte bStack_a;
  char local_6;
  undefined1 local_5;
  
  uVar4 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bStack_a = (byte)(param_2 >> 0x10);
  puVar3 = *(ushort **)(iVar1 + 0x58);
  if (bStack_a < 8) {
    local_40._0_2_ = CONCAT11((char)param_4,bStack_a);
    local_44 = 0x1c0008;
    local_6 = (char)(param_3 >> 0x10);
    if (param_4 != 2) {
      if (local_6 == '\0') {
        local_3c = local_3c & 0xffff;
      }
      else {
        param_3 = param_3 & 0xffff;
        if (*puVar3 < param_3) {
          do {
            uVar5 = uVar4;
            puVar3 = puVar3 + 1;
            uVar4 = uVar5 + 1;
            if (param_3 <= *puVar3) break;
          } while (uVar4 != 7);
          if (param_3 < *puVar3) {
            uVar4 = uVar5;
          }
          uVar4 = uVar4 & 0xff;
        }
        local_3c = CONCAT13((char)uVar4,CONCAT12(1,param_6._2_2_));
      }
      uVar2 = CmdExtWtblUpdate(param_1,param_2 & 0xffff,2,&local_44,0x1c);
      return uVar2;
    }
    if (local_6 != '\0') {
      local_5 = (undefined1)(param_3 >> 0x18);
      local_30._3_1_ = local_5;
      os_move_mem((void *)((int)&local_38 + 2),&param_5,6);
      local_30._0_3_ = CONCAT12(1,(ushort)bStack_a);
      uVar2 = CmdExtWtblUpdate(param_1,param_2 & 0xffff,2,&local_44,0x1c);
      return uVar2;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: unknown tid(%d)\n","MtAsicUpdateBASessionByFw",bStack_a);
  }
  return 1;
}

