
#include <stdio.h>
#include <stdbool.h>

#define GPU_START if(false) {}
#define CHECK_GPU(gpu_code_, gpu_name) \
  else if (gpu_code_ == gpu_code) { return gpu_name; }
#define GPU_END else { return NULL; }

char *find_gpu(int gpu_code) {
  GPU_START
  CHECK_GPU(0x3184, "GeminiLake [UHD Graphics 605]")
  CHECK_GPU(0x3185, "GeminiLake [UHD Graphics 600]")
  CHECK_GPU(0x3e90, "CoffeeLake-S GT1 [UHD Graphics 610]")
  CHECK_GPU(0x3e91, "CoffeeLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x3e92, "CoffeeLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x3e93, "CoffeeLake-S GT1 [UHD Graphics 610]")
  CHECK_GPU(0x3e96, "CoffeeLake-S GT2 [UHD Graphics P630]")
  CHECK_GPU(0x3e98, "CoffeeLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x3ea0, "WhiskeyLake-U GT2 [UHD Graphics 620]")
  CHECK_GPU(0x3ea5, "CoffeeLake-U GT3e [Iris Plus Graphics 655]")
  CHECK_GPU(0x4c8a, "RocketLake-S GT1 [UHD Graphics 750]")
  CHECK_GPU(0x4c90, "RocketLake-S GT1 [UHD Graphics P750]")
  CHECK_GPU(0x4c8b, "RocketLake-S GT1 [UHD Graphics 730]")
  CHECK_GPU(0x4c9a, "RocketLake-S [UHD Graphics]")
  CHECK_GPU(0x4e55, "JasperLake [UHD Graphics]")
  CHECK_GPU(0x4e61, "JasperLake [UHD Graphics]")
  CHECK_GPU(0x4e71, "JasperLake [UHD Graphics]")
  CHECK_GPU(0x5917, "UHD Graphics 620")
  CHECK_GPU(0x591c, "UHD Graphics 615")
  CHECK_GPU(0x87c0, "UHD Graphics 617")
  CHECK_GPU(0x9a60, "TigerLake-H GT1 [UHD Graphics]")
  CHECK_GPU(0x9a68, "TigerLake-H GT1 [UHD Graphics]")
  CHECK_GPU(0x9b41, "CometLake-U GT2 [UHD Graphics]")
  CHECK_GPU(0x9bc4, "CometLake-H GT2 [UHD Graphics]")
  CHECK_GPU(0x9bc5, "CometLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x9bc8, "CometLake-S GT2 [UHD Graphics 630]")
  CHECK_GPU(0x9bca, "Comet Lake UHD Graphics")
  CHECK_GPU(0x1606, "HD Graphics")
  CHECK_GPU(0x1612, "HD Graphics 5600")
  CHECK_GPU(0x1616, "HD Graphics 5500")
  CHECK_GPU(0x161e, "HD Graphics 5300")
  CHECK_GPU(0x1626, "HD Graphics 6000")
  CHECK_GPU(0x1902, "HD Graphics 510")
  CHECK_GPU(0x1906, "HD Graphics 510")
  CHECK_GPU(0x1912, "HD Graphics 530")
  CHECK_GPU(0x1916, "Skylake GT2 [HD Graphics 520]")
  CHECK_GPU(0x191b, "HD Graphics 530")
  CHECK_GPU(0x191d, "HD Graphics P530")
  CHECK_GPU(0x191e, "HD Graphics 515")
  CHECK_GPU(0x1921, "HD Graphics 520")
  CHECK_GPU(0x5902, "HD Graphics 610")
  CHECK_GPU(0x5912, "HD Graphics 630")
  CHECK_GPU(0x5916, "HD Graphics 620")
  CHECK_GPU(0x591b, "HD Graphics 630")
  CHECK_GPU(0x591d, "HD Graphics P630")
  CHECK_GPU(0x591e, "HD Graphics 615")
  CHECK_GPU(0x5923, "HD Graphics 635")
  CHECK_GPU(0x5a85, "HD Graphics 500")
  CHECK_GPU(0x1622, "Iris Pro Graphics 6200")
  CHECK_GPU(0x162a, "Iris Pro Graphics P6300")
  CHECK_GPU(0x162b, "Iris Graphics 6100")
  CHECK_GPU(0x1926, "Iris Graphics 540")
  CHECK_GPU(0x1927, "Iris Graphics 550")
  CHECK_GPU(0x192b, "Iris Graphics 555")
  CHECK_GPU(0x192d, "Iris Graphics P555")
  CHECK_GPU(0x1932, "Iris Pro Graphics 580")
  CHECK_GPU(0x193a, "Iris Pro Graphics P580")
  CHECK_GPU(0x193b, "Iris Pro Graphics 580")
  CHECK_GPU(0x193d, "Iris Pro Graphics P580")
  CHECK_GPU(0x3ea5, "CoffeeLake-U GT3e [Iris Plus Graphics 655]")
  CHECK_GPU(0x4905, "DG1 [Iris Xe MAX Graphics]")
  CHECK_GPU(0x4906, "DG1 [Iris Xe Pod]")
  CHECK_GPU(0x4907, "SG1 [Server GPU SG-18M]")
  CHECK_GPU(0x4908, "DG1 [Iris Xe Graphics]")
  CHECK_GPU(0x5926, "Iris Plus Graphics 640")
  CHECK_GPU(0x5927, "Iris Plus Graphics 650")
  CHECK_GPU(0x8a51, "Iris Plus Graphics G7 (Ice Lake)")
  CHECK_GPU(0x8a52, "Iris Plus Graphics G7")
  CHECK_GPU(0x8a56, "Iris Plus Graphics G1 (Ice Lake)")
  CHECK_GPU(0x8a5a, "Iris Plus Graphics G4 (Ice Lake)")
  CHECK_GPU(0x8a5c, "Iris Plus Graphics G4 (Ice Lake)")
  CHECK_GPU(0x9a49, "TigerLake-LP GT2 [Iris Xe Graphics]")
  GPU_END
}

