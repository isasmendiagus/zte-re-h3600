// module: mt7915.ko
// function: HQA_GetCfgOnOff @ 0x26eb18
// size: 380 bytes
//

undefined4 HQA_GetCfgOnOff(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  code *pcVar6;
  uint local_24;
  
  iVar1 = DebugLevel;
  uVar2 = *(uint *)(param_3 + 0xc);
  uVar2 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  local_24 = 0;
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0x10) >> 0x18);
  if (2 < iVar1) {
    printk("%s: Type:%d Band:%d\n","HQA_GetCfgOnOff",uVar2);
  }
  pcVar6 = *(code **)(iVar5 + 0xe8);
  if (pcVar6 == (code *)0x0) {
    FUN_0026cdd0(param_3,param_2,2,1);
    uVar3 = 1;
  }
  else {
    uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
    if ((uVar4 == 0x7915 ||
         (uVar4 == 0x6867 ||
         (uVar4 == 0x7663 ||
         (uVar4 == 0x6632 ||
         (uVar4 == 0x7615 ||
         (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7622))))) &&
       (uVar2 != 2)) {
      (*pcVar6)(param_1,uVar2,&local_24);
    }
    local_24 = local_24 << 0x18 | (local_24 >> 8 & 0xff) << 0x10 | (local_24 >> 0x10 & 0xff) << 8 |
               local_24 >> 0x18;
    *(uint *)(param_3 + 0xe) = local_24;
    FUN_0026cdd0(param_3,param_2,6,0);
    uVar3 = 0;
  }
  return uVar3;
}

