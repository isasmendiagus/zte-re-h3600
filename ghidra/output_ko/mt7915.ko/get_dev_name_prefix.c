// module: mt7915.ko
// function: get_dev_name_prefix @ 0x14ef28
// size: 164 bytes
//

undefined * get_dev_name_prefix(int param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined *puVar5;
  
  iVar2 = DAT_0033aa40;
  iVar3 = 0;
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  puVar4 = &_LANCHOR0;
  do {
    if (param_2 == iVar2) {
      if (DebugLevel < 3) {
        puVar5 = &DAT_0033aa44 + iVar3 * 0x14;
      }
      else {
        puVar5 = &DAT_0033aa44 + iVar3 * 0x14;
        printk("%s(): dev_idx = %d, dev_name_prefix=%s\n","get_dev_name_prefix",0,puVar5);
      }
      return puVar5;
    }
    iVar2 = *(int *)(puVar4 + 0x78);
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 0x14;
  } while (iVar2 != 0);
  return (undefined *)0x0;
}

