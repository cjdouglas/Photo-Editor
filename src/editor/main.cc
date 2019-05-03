#include "rendering/renderer.cc"

int main(void) {
  Renderer renderer;
  if (!renderer.InitializePrograms()) {
    std::cout << "Renderer failed to initalize programs" << std::endl;
    return -1;
  }
  renderer.DrawFrame();
}
