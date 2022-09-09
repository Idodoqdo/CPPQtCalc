#include "controller.h"

double Controller::Calculate(double x) { return model->Calculate(x); }

void Controller::AppendToLine(std::string added_string) {
  model->AppendToLine(added_string);
}

void Controller::AC() { model->AC(); }

void Controller::CalculateGraph(std::vector<double> &x, std::vector<double> &y,
                                double &xBegin, double &xEnd, double &yBegin,
                                double &yEnd, double &step) {
  model->CalculateGraph(x, y, xBegin, xEnd, yBegin, yEnd, step);
}

bool Controller::Valid() {
    return model->Valid();
}
