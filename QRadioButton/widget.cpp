#include "widget.h"
#include "ui_widget.h"
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QRadioButton *rb1 = new QRadioButton("QRadioButton001");
    QRadioButton *rb2 = new QRadioButton("QRadioButton002");
    QRadioButton *rb3 = new QRadioButton("QRadioButton003");

    QButtonGroup *group = new QButtonGroup(this);//按钮组
    group->setObjectName("group");

    group->addButton(rb1);
    group->addButton(rb2);
    group->addButton(rb3);

    //保存按钮
    QPushButton *save = new QPushButton("save");


    //垂直布局器
    QVBoxLayout *vb= new QVBoxLayout(this);
    //遍历按钮组加入布局其
    for(int i = 0 ;i<group->buttons().size();i++)
    {
        vb->addWidget(group->buttons()[i]);
    }
    vb->addWidget(save);
    connect(save,&QPushButton::clicked,this,&Widget::save);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::save()
{
    //获取按钮组  模板函数 获取到group
    QButtonGroup *group = this->findChild<QButtonGroup *>("group");
    if(!group)
        return;

    //获取被选中的按钮
    QRadioButton *but = (QRadioButton *) group->checkedButton();
    if(!but)
    {
        QMessageBox::warning(this, "" ,"empty");
        return;
    }
    QMessageBox::information(this,"",but->text());
}
