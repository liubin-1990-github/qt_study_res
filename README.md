# qt_study_res

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

QRadioButton 加入group 通过遍历group 添加到布局器中
group->setObjectName("group");
在另外的函数中获取group
QButtonGroup *group = this->findChild<QButtonGroup *>("group");

————————————————————————————————————————————--------------------------------------------------------------------分割线
----------------------------------------------------------------



QComboBox中添加数据

    ui->setupUi(this);
    ui->comboBox->clear();

    ui->comboBox->addItem("Item001");
    ui->comboBox->addItem("Item002");

    

    ui->comboBox->addItem(QIcon(),"Item003");
    QStringList s1 = {"4","5"};

    ui->comboBox->addItems(s1);

    ui->comboBox->insertItem(1,"insert");
    
    
    QComboBox中插入自定义数据 访问自定义数据
    
    //自定义数据
    struct MyType
{
    int x = 0;
    int y =0;
    MyType() {}
};
Q_DECLARE_METATYPE(MyType)

{

//插入自定义数据
    QVariant var;
    MyType my;
    my.x=101;
    var.setValue(my);
    ui->comboBox->addItem("Item001",var);
}


//访问自定义数据
void Widget::on_pushButton_clicked()
{
    qDebug()<<ui->comboBox->itemText(0);
    QVariant var = ui->comboBox->itemData(0);
    qDebug()<< "var.value<MyType>().x ="<<var.value<MyType>().x;
}


