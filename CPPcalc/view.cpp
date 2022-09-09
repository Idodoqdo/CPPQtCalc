#include "View.h"

#include "ui_view.h"

View::View(Controller *_controller)
    : controller(_controller), ui(new Ui::View) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_multiplication, SIGNAL(clicked()), this,
          SLOT(AppendToLine()));
  connect(ui->pushButton_division, SIGNAL(clicked()), this,
          SLOT(AppendToLine()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_left_s, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_right_s, SIGNAL(clicked()), this,
          SLOT(AppendToLine()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(AppendToLine()));
    connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(AppendToLine()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AC()));
}

View::~View() { delete ui; }

void View::AppendToLine() {
  QPushButton *button = (QPushButton *)sender();
  QString numbers = "0123456789";
  if ((*ui->label->text().rbegin() == '.' ||
       *ui->label->text().rbegin() == '/' ||
       *ui->label->text().rbegin() == '*' ||
       *ui->label->text().rbegin() == '+' ||
       *ui->label->text().rbegin() == '-' ||
       *ui->label->text().rbegin() == 'd' ||
       *ui->label->text().rbegin() == '^' ||
       *ui->label->text().rbegin() == '(') &&
      (button->text() == "." || button->text() == '/' ||
       button->text() == "*" || button->text() == "mod" ||
       button->text() == '^')) {
  } else if ((*ui->label->text().rbegin() == 'x' &&
              (button->text() == 'x' ||
               numbers.indexOf(button->text()) != -1)) ||
             (numbers.indexOf(*ui->label->text().rbegin()) != -1 &&
              button->text() == 'x')) {
  } else {
    ui->label->setText(ui->label->text().append(button->text()));
    controller->AppendToLine(button->text().toStdString());
  }
}

void View::AC() {
  ui->label->clear();
  controller->AC();
}

void View::on_PushButtonEquals_clicked() {
  bool valid = controller->Valid();
  if (valid) {
    double res;
    double x = ui->doubleSpinBox->value();
    res = controller->Calculate(x);
    ui->label->setText(QString::number(res));
  } else {
    ui->label->setText("Error");
  }
}

void View::on_PushButtonBuildGraph_clicked() {
  bool valid = controller->Valid();
  if (valid) {
  ui->widget->clearGraphs();
  double xBegin, xEnd, yBegin, yEnd, step;
  std::vector<double> x, y;
  xBegin = ui->doubleSpinBox_min_Df->value();
  xEnd = ui->doubleSpinBox_max_Df->value();
  yBegin = ui->doubleSpinBox_min_Ef->value();
  yEnd = ui->doubleSpinBox_max_Ef->value();
  step = ui->doubleSpinBox_step->value();
  controller->CalculateGraph(x, y, xBegin, xEnd, yBegin, yEnd, step);
  QVector<double> Qx = QVector<double>(x.begin(), x.end());
  QVector<double> Qy = QVector<double>(y.begin(), y.end());
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(Qx, Qy);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  } else {
      ui->label->setText("Error");
  }
}
