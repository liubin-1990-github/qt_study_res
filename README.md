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
Q_DECLARE_METATYPE(MyType)
void Widget::on_pushButton_clicked()
{
    qDebug()<<ui->comboBox->itemText(0);
    QVariant var = ui->comboBox->itemData(0);
    qDebug()<< "var.value<MyType>().x ="<<var.value<MyType>().x; //模板函数获取
}
    
   comboBox 的一些信号
    {
            connect(ui->comboBox,SIGNAL(activated(int)),this,SLOT(sel(int)));
    connect(ui->comboBox,SIGNAL(activated(QString)),this,SLOT(sel(QString))); //只有用户选择激发
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(cur(int)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(cur(QString)));//用户选择和代码都可以激发
    connect(ui->comboBox,SIGNAL(highlighted(int)),this,SLOT(hi(int)));
    }
    
    
    -----------------------------------------
    
    -----------------------------------------------------------------------------------------------------------
    QListWidget
    
    selectionMode

    flow 从上到下还是从左到右
    gridSize 每一行的宽高
    iconSize 图标的宽高
    
    
    {
    ui->setupUi(this);
    ui->listWidget->clear();

    //插入数据的各种方法
    QListWidgetItem *item1=new QListWidgetItem;
    item1->setText(QString::fromLocal8Bit("测试数据1"));
    ui->listWidget->insertItem(0,item1);

    new QListWidgetItem("test item2",ui->listWidget);
    
    ui->listWidget->addItem("test item3");
    //插入包含图标的数据
    QListWidgetItem *itemIcon = new QListWidgetItem;
    itemIcon->setText("test item icon");
    itemIcon->setIcon(QIcon("path"));
    ui->listWidget->addItem(itemIcon);
}
    
       //遍历列表
    for(int i = 0 ; i<ui->listWidget->count();i++)
    {
        qDebug()<<ui->listWidget->item(i)->text();

    }
    //设置可编辑状态
    //所有时间都激发编辑 双击选择 选项变化
    ui->listWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
    for(int i = 0 ; i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    }
   QListWidget 排序
    {
    static bool isDesc = false;
    if(!isDesc)
    {
        ui->listWidget->sortItems(Qt::DescendingOrder);
    }
    else
    {
        ui->listWidget->sortItems(Qt::AscendingOrder);
    }
    isDesc=!isDesc;
}
    
    ListWidget信号  。。。
    listWidget可以显示其他控件
    
    ------------------------------------------------------------
    
    ------------------------------------------------------------
    
    ------------------------------------------------------------
     if(event->isAutoRepeat()) return; 
    
    void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    if(event->key()==Qt::Key_F1)
    {
        qDebug()<<"F1";
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{

}
    
    
    


