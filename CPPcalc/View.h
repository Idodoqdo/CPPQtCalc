#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Controller *controller;
  Q_OBJECT

public:
  explicit View(Controller *_controller);
  ~View();

private:
  Ui::View *ui;
private slots:
  void AppendToLine();
  void AC();
  void on_PushButtonEquals_clicked();
  void on_PushButtonBuildGraph_clicked();
};
#endif // VIEW_H
