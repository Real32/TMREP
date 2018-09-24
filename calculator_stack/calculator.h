#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QWidget>
#include <QStack>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget
 {
  Q_OBJECT
  private:
   QLabel *display;
   QStack <QString> stack;
  public:
   Calculator (QWidget* pwgt = 0);
   QPushButton* createButton (const QString& str);
   void calculate ();
  public slots:
   void slotButtonClicked ();
 };
#endif //CALCULATOR_H
