#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"

class Controller {
  Model *model;

 public:
  Controller(Model *m) : model(m){};
  double Calculate(double x = 0);
  void AppendToLine(std::string added_string);
  void AC();
  void CalculateGraph(std::vector<double> &x, std::vector<double> &y,
                      double &xBegin, double &xEnd, double &yBegin,
                      double &yEnd, double &step);
  bool Valid();
};

#endif  // CONTROLLER_H
