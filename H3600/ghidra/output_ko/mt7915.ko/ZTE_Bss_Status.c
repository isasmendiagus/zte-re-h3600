// module: mt7915.ko
// function: ZTE_Bss_Status @ 0x160a10
// size: 40 bytes
//

undefined4 ZTE_Bss_Status(int *param_1)

{
  ZTE_Bss_Report_Info_Active(param_1,*(undefined1 *)(*param_1 + 0x3c),1);
  ZTE_Bss_NotifyAD(param_1);
  return 1;
}

