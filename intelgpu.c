
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define GPU_START if(false) {}
#define CHECK_GPU(gpu_code_, gpu_name)                    \
  else if (gpu_code_ == gpu_code){                        \
    char *ret = malloc(sizeof(char)*strlen(gpu_name)+1);  \
    strcpy(ret, gpu_name);                                \
    return ret;                                           \
  }
#define GPU_END else { return NULL; }

char *find_gpu(int gpu_code) {
  GPU_START
  CHECK_GPU(0x3184, "Intel GeminiLake [UHD Graphics 605]")
  CHECK_GPU(0x3185, "Intel GeminiLake [UHD Graphics 600]")
  CHECK_GPU(0x3e90, "Intel CoffeeLake-S GT1 [UHD Graphics 610]")
  CHECK_GPU(0x3e91, "Intel CoffeeLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x3e92, "Intel CoffeeLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x3e93, "Intel CoffeeLake-S GT1 [UHD Graphics 610]")
  CHECK_GPU(0x3e96, "Intel CoffeeLake-S GT2 [UHD Graphics P630]")
  CHECK_GPU(0x3e98, "Intel CoffeeLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x3ea0, "Intel WhiskeyLake-U GT2 [UHD Graphics 620]")
  CHECK_GPU(0x3ea5, "Intel CoffeeLake-U GT3 [Iris Plus Graphics 655]")
  CHECK_GPU(0x4c8a, "Intel RocketLake-S GT1 [UHD Graphics 750]")
  CHECK_GPU(0x4c90, "Intel RocketLake-S GT1 [UHD Graphics P750]")
  CHECK_GPU(0x4c8b, "Intel RocketLake-S GT1 [UHD Graphics 730]")
  CHECK_GPU(0x4c9a, "Intel RocketLake-S [UHD Graphics]")
  CHECK_GPU(0x4e55, "Intel JasperLake [UHD Graphics]")
  CHECK_GPU(0x4e61, "Intel JasperLake [UHD Graphics]")
  CHECK_GPU(0x4e71, "Intel JasperLake [UHD Graphics]")
  CHECK_GPU(0x5917, "Intel UHD Graphics 620")
  CHECK_GPU(0x591c, "Intel UHD Graphics 615")
  CHECK_GPU(0x87c0, "Intel UHD Graphics 617")
  CHECK_GPU(0x9a60, "Intel TigerLake-H GT1 [UHD Graphics]")
  CHECK_GPU(0x9a68, "Intel TigerLake-H GT1 [UHD Graphics]")
  CHECK_GPU(0x9b41, "Intel CometLake-U GT2 [UHD Graphics]")
  CHECK_GPU(0x9bc4, "Intel CometLake-H GT2 [UHD Graphics]")
  CHECK_GPU(0x9bc5, "Intel CometLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x9bc8, "Intel CometLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x9bca, "Intel Comet Lake UHD Graphics")
  CHECK_GPU(0x1606, "Intel HD Graphics")
  CHECK_GPU(0x1612, "Intel HD Graphics 5600")
  CHECK_GPU(0x1616, "Intel HD Graphics 5500")
  CHECK_GPU(0x161e, "Intel HD Graphics 5300")
  CHECK_GPU(0x1626, "Intel HD Graphics 6000")
  CHECK_GPU(0x1902, "Intel HD Graphics 510")
  CHECK_GPU(0x1906, "Intel HD Graphics 510")
  CHECK_GPU(0x1912, "Intel HD Graphics 530")
  CHECK_GPU(0x1916, "Intel Skylake GT2 [HD Graphics 520]")
  CHECK_GPU(0x191b, "Intel HD Graphics 530")
  CHECK_GPU(0x191d, "Intel HD Graphics P530")
  CHECK_GPU(0x191e, "Intel HD Graphics 515")
  CHECK_GPU(0x1921, "Intel HD Graphics 520")
  CHECK_GPU(0x5902, "Intel HD Graphics 610")
  CHECK_GPU(0x5912, "Intel HD Graphics 630")
  CHECK_GPU(0x5916, "Intel HD Graphics 620")
  CHECK_GPU(0x591b, "Intel HD Graphics 630")
  CHECK_GPU(0x591d, "Intel HD Graphics P630")
  CHECK_GPU(0x591e, "Intel HD Graphics 615")
  CHECK_GPU(0x5923, "Intel HD Graphics 635")
  CHECK_GPU(0x5a85, "Intel HD Graphics 500")
  CHECK_GPU(0x1622, "Intel Iris Pro Graphics 6200")
  CHECK_GPU(0x162a, "Intel Iris Pro Graphics P6300")
  CHECK_GPU(0x162b, "Intel Iris Graphics 6100")
  CHECK_GPU(0x1926, "Intel Iris Graphics 540")
  CHECK_GPU(0x1927, "Intel Iris Graphics 550")
  CHECK_GPU(0x192b, "Intel Iris Graphics 555")
  CHECK_GPU(0x192d, "Intel Iris Graphics P555")
  CHECK_GPU(0x1932, "Intel Iris Pro Graphics 580")
  CHECK_GPU(0x193a, "Intel Iris Pro Graphics P580")
  CHECK_GPU(0x193b, "Intel Iris Pro Graphics 580")
  CHECK_GPU(0x193d, "Intel Iris Pro Graphics P580")
  CHECK_GPU(0x3ea5, "Intel CoffeeLake-U GT3e [Iris Plus Graphics 655]")
  CHECK_GPU(0x4905, "Intel DG1 [Iris Xe MAX Graphics]")
  CHECK_GPU(0x4906, "Intel DG1 [Iris Xe Pod]")
  CHECK_GPU(0x4907, "Intel SG1 [Server GPU SG-18M]")
  CHECK_GPU(0x4908, "Intel DG1 [Iris Xe Graphics]")
  CHECK_GPU(0x5926, "Intel Iris Plus Graphics 640")
  CHECK_GPU(0x5927, "Intel Iris Plus Graphics 650")
  CHECK_GPU(0x8a51, "Intel Iris Plus Graphics G7 (Ice Lake)")
  CHECK_GPU(0x8a52, "Intel Iris Plus Graphics G7")
  CHECK_GPU(0x8a56, "Intel Iris Plus Graphics G1 (Ice Lake)")
  CHECK_GPU(0x8a5a, "Intel Iris Plus Graphics G4 (Ice Lake)")
  CHECK_GPU(0x8a5c, "Intel Iris Plus Graphics G4 (Ice Lake)")
  CHECK_GPU(0x9a49, "Intel TigerLake-LP GT2 [Iris Xe Graphics]")
  GPU_END
}

