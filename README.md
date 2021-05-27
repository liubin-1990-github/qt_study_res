QMAKE_CFLAGS += -fexec-charset=UTF-8 -finput-charset=GBK
QMAKE_CXXFLAGS += -fexec-charset=UTF-8 -finput-charset=GBK
'-finput-charset' : 指定源文件的编码（默认UTF-8）

'-fexec-charset' : 指定多字节字符串(const char*)常量在编译后的程序里保存的编码集（默认UTF-8）

'-fwide-exec-charset' : 指定宽字节字符串(const wchar_t*)常量在编译后的程序里的保存的编码集


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
    
    --------------------------------------------------------------------------------------------
    -----------------------------------------------
    QTableWidget
    {
    ui->setupUi(this);
    //清空所有标题和内容
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("13232"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("22323232"));
        //设置标题列的宽度
    ui->tableWidget->setColumnWidth(0,200);

    //设置垂直标题
    ui->tableWidget->setRowCount(3);
    QStringList List = {"1","2","3"};
    ui->tableWidget->setVerticalHeaderLabels(List);


}
    setRowCount(5) 会删除多余的item'控件
        //插入数据，
    ui->tableWidget->setItem(1,1,new QTableWidgetItem("insert 1"));// row 1 col 1   插入

    //结尾加一行
    int row =ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    
        //插入QIcon图片
    ui->tableWidget->item(0,1)->setIcon(QIcon(NULL));
    ui->tableWidget->setRowHeight(0,80);
    ui->tableWidget->setIconSize(QSize(ui->tableWidget->rowHeight(0),ui->tableWidget->rowHeight(0)));
    
    //charu widget图片
    
    QLabel *img = new QLabel();
    QPixmap pix("path");
    pix=pix.scaled(ui->tableWidget->columnWidth(0),ui->tableWidget->rowHeight(row));
    img->setPixmap(pix);
    ui->tableWidget->setCellWidget(row ,0,img);
    
    void Widget::on_pushButton_clicked()
{
    //空行无法选择
    QList<QTableWidgetItem *> item =ui->tableWidget->selectedItems();//获取鼠标选中的item 存入item中 空行无法选择
    for(int i =0;i<item.size();i++)
    {
        qDebug()<<item[i]->row()<<" ;"<<item[i]->column()<<" text="<<item[i]->text();
    }


    //选择模式器
    QItemSelectionModel *model  =  ui->tableWidget->selectionModel();
    //获取所有的选择索引
    QModelIndexList slist = model->selectedIndexes();

    //获取所有被选中的行号
    std::set<int> row;
    for(int i = 0;i<slist.size();i++)
    {
        //重复的会插入失败
        row.insert(slist[i].row());
    }

    QString msg =QStringLiteral("确认删除");
    for(std::set<int >::iterator itr=row.begin();itr!=row.end();itr++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(*itr,0);
        msg +="[";
        msg+=QString::number(*itr+1);
        msg+=":";
        if(item)
            msg +=item->text();
        msg+="]";

    }
    QMessageBox::information(this,"",msg,QStringLiteral("确认"),QStringLiteral("取消"));

    //删除多行
    for(;;)
    {
        //获取所有的选择索引
        QModelIndexList s = model->selectedIndexes();
        if(s.size()<=0) break;

        //每次只删除一行
        ui->tableWidget->removeRow(s[0].row());
    }

}
    
    
    
    


