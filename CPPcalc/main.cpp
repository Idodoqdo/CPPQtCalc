#include "View.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  View w(&controller);
  w.show();
  return a.exec();
}
