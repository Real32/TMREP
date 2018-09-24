#include "calculator.h"

Calculator::Calculator (QWidget *parent) : QWidget(parent)
{
 display = new QLabel("");
 display->setMinimumSize (150, 50);
 QChar arr[4][4] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'0', '.', '=', '+'}
 };

 QGridLayout *myLayout = new QGridLayout;
 myLayout->addWidget(display, 0, 0, 1, 4);
 myLayout->addWidget(createButton("C"), 1, 3);
 for (int i = 0; i < 4; ++i)
 {
  for (int j = 0; j < 4; ++j)
  {
   myLayout->addWidget(createButton(arr[i][j]), i + 2, j);
  }
 }
 setLayout(myLayout);
}

QPushButton* Calculator::createButton (const QString& str)
{
 QPushButton* pcmd = new QPushButton(str);
 pcmd->setMinimumSize(40, 40);
 connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
 return pcmd;
}

void Calculator::calculate()
{
 double second = stack.pop().toDouble();
 QString operation = stack.pop();
 double first = stack.pop().toDouble();
 double result = 0;

 if (operation == "+")
 {
     result = first + second;
 }
 else if (operation == "-")
 {
     result = first - second;
 }
 else if
         (operation == "*")
 {
     result = first * second;
 }
 else if (operation == "/")
 {
     result = first / second;
 }
 display->setText(QString("%1").arg(result, 0, 'f', 3));
}

void Calculator::slotButtonClicked()
{
 QString str = ((QPushButton*)sender())->text();
 if (str == "C")
 {
  stack.clear();
  display->setText("");
  return;
 }

 QString text = display->text();
 int len = text.length();
 QString last = "";

 if (len>0)
 {
     last = text.right(1);
 }

 if (((len==0 && stack.count()==0) ||((stack.count()==2 && len>1 && (last=="+"||last=="-"||last=="*"||last=="/")))) &&
     (str.contains(QRegExp("[0-9]")) || str=="-"))
 {
    text=str;
 }
 else if ((text+str).contains(QRegExp("^-?[0-9]+\\.?[0-9]*$")))
 {
  text+=str;
 }
 else if (text.contains(QRegExp("^-?[0-9]+\\.?[0-9]*$")))
 {
  if (str=="*"||str=="/"||str=="+"||str=="-"||str=="=")
  {
   if (stack.count()==2)
   {
    stack.push(text);
    calculate();
    text=display->text();
   }
   if (str!="=")
   {
    stack.push(text);
    text+=str;
    stack.push(str);
   }
  }
 }
 display->setText(text);
}




