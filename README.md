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
    
    
    
    -----------------------------------------------------
    treeWidget
    
    
     //添加顶部标题
    ui->treeWidget->headerItem()->setText(0,"标题1");
    ui->treeWidget->headerItem()->setText(1,"head2");
    ui->treeWidget->headerItem()->setText(2,"head3");
    ui->treeWidget->headerItem()->setText(3,"head4");





//    ui->treeWidget->topLevelItem(i)->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);

    //插入数据  在结尾出插入
    ui->treeWidget->addTopLevelItem(new QTreeWidgetItem);
    ui->treeWidget->topLevelItem(0)->setText(0,"tree node 1");
    ui->treeWidget->topLevelItem(0)->setText(1,"tree node 11");

    ui->treeWidget->addTopLevelItem(new QTreeWidgetItem({"tree node 31","tree node 32"}));
    //开头插入
    ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem({"insert 1","insert 2"}));
    //结尾插入
    ui->treeWidget->insertTopLevelItem(ui->treeWidget->topLevelItemCount(),new QTreeWidgetItem({"insert end 1","insert end 2"}));
    // 直接new
    QTreeWidgetItem *node = new QTreeWidgetItem(ui->treeWidget);
    node ->setText(0,"new");

    ui->treeWidget->topLevelItem(0)->addChild(new QTreeWidgetItem({"child1"}));
    ui->treeWidget->topLevelItem(0)->addChild(new QTreeWidgetItem({"child2"}));
    ui->treeWidget->topLevelItem(0)->addChild(new QTreeWidgetItem({"child3"}));

    ui->treeWidget->topLevelItem(0)->child(0)->addChild(new QTreeWidgetItem({"2-chilid1"}));

    ui->treeWidget->topLevelItem(1)->addChild(new QTreeWidgetItem({"child11"}));
    ui->treeWidget->topLevelItem(1)->addChild(new QTreeWidgetItem({"child12"}));


    //插入图片
    ui->treeWidget->setIconSize(QSize(60,60));
    ui->treeWidget->topLevelItem(0)->setIcon(0,QIcon());

    //插入widget 控件

    QPushButton *btn = new QPushButton("test");
    ui->treeWidget->setItemWidget(ui->treeWidget->topLevelItem(1),0,btn);
    
    
    ------------------------------------------------、-
    -----------------------------------------------
    qDialog
    
    
    //cbuiltindlg.h头文件

#ifndef CBUILTINDLG_H
#define CBUILTINDLG_H
#include <QDialog>
#include <QGridLayout>
class QTextEdit;
class QPushButton;
class CBuiltinDlg : public QDialog
{
    Q_OBJECT
public:
    explicit CBuiltinDlg(QWidget *parent = 0);
    virtual ~CBuiltinDlg();
private:
    QTextEdit   * displayTextEdit;
    QPushButton *colorPushBtn;
    QPushButton *errorPushBtn;
    QPushButton *filePushBtn;
    QPushButton *fontPushBtn;
    QPushButton *inputPushBtn;
    QPushButton *pagePushBtn;
    QPushButton *progressPushBtn;
    QPushButton *printPushBtn;
private slots:
    void doPushBtn();
};
#endif // CBUILTINDLG_H
 



#include "cbuiltindlg.h"
#include <QtGui/QtGui>
CBuiltinDlg::CBuiltinDlg(QWidget *parent) :
    QDialog(parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    displayTextEdit = new QTextEdit(tr("Qt的标准通用对话框。"));
    QGridLayout *gridLayout = new QGridLayout;
    colorPushBtn = new QPushButton(tr("颜色对话框"));
    errorPushBtn = new QPushButton(tr("错误消息框"));
    filePushBtn  = new QPushButton(tr("文件对话框"));
    fontPushBtn  = new QPushButton(tr("字体对话框"));
    inputPushBtn = new QPushButton(tr("输入对话框"));
    pagePushBtn  = new QPushButton(tr("页设置对话框"));
    progressPushBtn = new QPushButton(tr("进度对话框"));
    printPushBtn  = new QPushButton(tr("打印对话框"));
    gridLayout->addWidget(colorPushBtn,0,0,1,1);
    gridLayout->addWidget(errorPushBtn,0,1,1,1);
    gridLayout->addWidget(filePushBtn,0,2,1,1);
    gridLayout->addWidget(fontPushBtn,1,0,1,1);
    gridLayout->addWidget(inputPushBtn,1,1,1,1);
    gridLayout->addWidget(pagePushBtn,1,2,1,1);
    gridLayout->addWidget(progressPushBtn,2,0,1,1);
    gridLayout->addWidget(printPushBtn,2,1,1,1);
    gridLayout->addWidget(displayTextEdit,3,0,3,3);
    setLayout(gridLayout);
    connect(colorPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(errorPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(filePushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(fontPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(inputPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(pagePushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(progressPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(printPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    setWindowTitle(tr("内建对话框"));
    resize(400,300);
}
CBuiltinDlg::~CBuiltinDlg()
{
}
void CBuiltinDlg::doPushBtn()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn == colorPushBtn)  //颜色对话框
    {
        QPalette palette = displayTextEdit->palette();
        const QColor& color =
                QColorDialog::getColor(palette.color(QPalette::Base),this);
        if (color.isValid())
        {
            palette.setColor(QPalette::Base,color);
            displayTextEdit->setPalette(palette);
        }
    }
    else if (btn == errorPushBtn)   //错误对话框
    {
        QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
        QErrorMessage box(this);
        box.setWindowTitle(tr("错误消息框"));
        box.showMessage(tr("错误消息框实例XX"));
        box.showMessage(tr("错误消息框实例XX"));
        box.showMessage(tr("错误消息框实例xx"));
        box.showMessage(tr("错误消息框实例yy"));
        box.showMessage(tr("错误消息框实例zz"));
        box.exec();
    }
    else if (btn == filePushBtn) //文件对话框
    {
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("打开文件"),
                    "/usr/local/Trolltech",
                    tr("任何文件(*.*)"
                    ";;文本文件(*.txt)"
                    ";;XML文件(*.xml)"));
        displayTextEdit->setText(fileName);
    }
    else if (btn == fontPushBtn)   //字体对话框
    {
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok,
                                                 displayTextEdit->font(),
                                                 this,
                                                 tr("字体对话框"));
        if (ok)   //如果<确定>，设置字体
        {
            displayTextEdit->setFont(font);
        }
    }
    else if (btn == inputPushBtn) //输入对话框
    {
        bool ok;
        QString text = QInputDialog::getText(this,
                                             tr("输入对话框"),
                                             tr("输入文件"),
                                             QLineEdit::Normal,
                                             QDir::home().dirName(),
                                             &ok);
        if (ok && !text.isEmpty())
            displayTextEdit->setText(text);
    }
    else if (btn == pagePushBtn) //页设置对话框
    {
        QPrinter printer;
        QPageSetupDialog dlg(&printer,this);
        dlg.setWindowTitle(tr("页设置对话框"));
        if (dlg.exec() == QDialog::Accepted)
        {
            //进行页面的设置处理
        }
    }
    else if (btn == progressPushBtn) //进度对话框
    {
        QProgressDialog progress(tr("正在复制文件"),
                                tr("取消"),
                                0,
                                10000,
                                this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setWindowTitle(tr("进度对话框"));
        progress.show();
        for (int i=0; i<10000; i++)
        {
            progress.setValue(i);
            qApp->processEvents();
            if (progress.wasCanceled())
            {
                break;
            }
            //复制文件处理
            qDebug()<<i;
        }
       progress.setValue(10000);
    }
    else if (btn == printPushBtn)//打印对话框
    {
         QPrinter printer;
         QPrintDialog dlg(&printer,this);
         dlg.setWindowTitle(tr("打印对话框"));
         if (dlg.exec() == QDialog::Accepted)
         {
             //进行下一步处理
         }
    }
}
 

//main.cpp主函数文件

#include <QtGui/QApplication>
#include "dialog.h"
#include "cbuiltindlg.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBuiltinDlg *dd = new CBuiltinDlg;
    dd->show();
    return a.exec();
}
    ----------------------------------------
    qGridlayout
    
    
        QApplication a(argc, argv);
    Widget w;

    QWidget* q = new QWidget;
    QGridLayout *gl = new QGridLayout(q);
    QPushButton *but1 =new QPushButton("but1");

    gl->addWidget(but1,0,0);

    QPushButton *but2 =new QPushButton("but2");

    gl->addWidget(but2,0,1);

    QPushButton *but3=new QPushButton("but3");

    gl->addWidget(but3,0,3);

    QPushButton *but4 =new QPushButton("but4");

    gl->addWidget(but4,0,4);
    gl->setHorizontalSpacing(100);
    gl->setVerticalSpacing(10);
    
    
    


