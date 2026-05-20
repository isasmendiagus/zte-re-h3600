// module: tm.ko
// function: zte_api_set_g988_cpu_not_drop_staen @ 0x63be4
// size: 32 bytes
//

int zte_api_set_g988_cpu_not_drop_staen(int param_1)

{
  int iVar1;
  
  iVar1 = pm_set_g988_cpu_not_drop_staen(param_1 != 0);
  return -(uint)(iVar1 != 0);
}

