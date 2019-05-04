#include <nanogui/screen.h>

class App : public nanogui::Screen {
public:
  App();
  virtual void draw(NVGcontext *ctx);
};
