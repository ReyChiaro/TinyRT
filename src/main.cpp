#include <iostream>
#include <thread>

int main() {
  using namespace std::chrono_literals;

  unsigned int img_h = 256;
  unsigned int img_w = 256;

  std::cout << "P3" << std::endl;
  std::cout << img_h << " " << img_w << std::endl;
  std::cout << 255 << std::endl;

  for (unsigned int h = 0; h < img_h; h += 1) {
    std::clog << "\rScanlines: " << (h + 1) << " " << std::flush;
    std::this_thread::sleep_for(10ms);
    for (unsigned int w = 0; w < img_w; w += 1) {

      int r = static_cast<int>((double)h / (img_h - 1) * 255);
      int g = static_cast<int>((double)w / (img_w - 1) * 255);
      int b = 0;

      std::cout << r << " " << g << " " << b << " ";
    }
    std::cout << std::endl;
  }
  std::clog << "\nDone." << std::endl;

  return 0;
}
