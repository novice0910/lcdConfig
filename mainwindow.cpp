#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    dataInit();
    toolBarCreate();
    allWidgetCreate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toolBarCreate()
{
    //about project
    QToolBar *toolBarProject = new QToolBar;
    this->addToolBar(toolBarProject);
    this->addToolBarBreak(Qt::TopToolBarArea);
    QAction *newProject = new QAction(tr("新建"),this);
    newProject->setToolTip(tr("新建工程"));
    connect(newProject,SIGNAL(triggered()),this,SLOT(actionNewProject()));
    toolBarProject->addAction(newProject);
    QAction *openProject = new QAction(tr("打开"),this);
    openProject->setToolTip(tr("打开工程"));
    connect(openProject,SIGNAL(triggered()),this,SLOT(actionOpenProject()));
    toolBarProject->addAction(openProject);
    QAction *actionSaveProject = new QAction(tr("Debug"),this);
    actionSaveProject->setToolTip(tr("生成配置文件"));
    connect(actionSaveProject,SIGNAL(triggered()),this,SLOT(slotSaveProject()));
    toolBarProject->addAction(actionSaveProject);
    QAction *setProject = new QAction(tr("设置"),this);
    setProject->setToolTip(tr("串口设置"));
    connect(setProject,SIGNAL(triggered()),this,SLOT(actionSetProject()));
    toolBarProject->addAction(setProject);
    //draw the item
    QToolBar *toolBar = new QToolBar;
    this->addToolBar(toolBar);
    QAction *drawAciton = new QAction(tr("按键"),this);
    drawAciton->setToolTip(tr("按键返回"));
    toolBar->addAction(drawAciton);
    connect(drawAciton,SIGNAL(triggered()),this,SLOT(slotDrawBtnTriggered()));
    toolBar->addAction(tr("显示框"),this,SLOT(slotDrawLabTrigger()));
}

void MainWindow::allWidgetCreate()
{
    centralWidgetCreate();
    leftDockWidgetCreate();
    rightDockWidgetCreate();
}

void MainWindow::centralWidgetCreate()
{
    tabWidget = new QTabWidget(ui->centralWidget);
    QWidget * tab_1 = new QWidget(tabWidget);
    QWidget * tab_2 = new QWidget(tabWidget);
    tabWidget->addTab(tab_1,tr("欢迎使用"));
    tabWidget->addTab(tab_2,tr("配置"));
    tabWidget->resize(900,this->height());
    QLabel * lab = new QLabel(tr("欢迎使用!"),tab_1);
    lab->setGeometry(0,0,300,50);
    stackedView = new QStackedWidget(tab_2);
    stackedView->resize(QSize(850,480));
    stackedView->move(20,0);
}

void MainWindow::leftDockWidgetCreate()
{
    dockWidgetPageProperty = new QDockWidget("image",this);
    dockWidgetPageProperty->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidgetPageProperty->setFeatures(QDockWidget::DockWidgetMovable);
    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidgetPageProperty);
    QMainWindow *leftDockMainwindow = new QMainWindow;
    leftDockMainwindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    dockWidgetPageProperty->setWidget(leftDockMainwindow);
    leftDockMainwindow->setParent(dockWidgetPageProperty);
    pageTableWidget = new QTableWidget(leftDockMainwindow);
    leftDockMainwindow->setCentralWidget(pageTableWidget);
    QStringList header;
    header<<tr("页码")<<tr("文件");
    pageTableWidget->setColumnCount(2);
    pageTableWidget->setHorizontalHeaderLabels(header);
    pageTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    pageTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//item no edit
    connect(pageTableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(slotPageTableWidgetSelectedChanged()));

    QMenu *menu = new QMenu;
    menu->addAction(tr("删除选中行"),this,SLOT(actionDeleteOnePage()));
    menu->addAction(tr("删除所有"),this,SLOT(actionDeleteAllPage()));
    QPushButton *btn = new QPushButton("删除");
    btn->setMenu(menu);

    QToolBar *pToolBar = leftDockMainwindow->addToolBar("new");
    pToolBar->addAction(tr("新增"),this,SLOT(actionNewPage()));
    pToolBar->addWidget(btn);
    pToolBar->addAction(tr("上移"),this,SLOT(actionPageUp()));
    pToolBar->addAction(tr("下移"),this,SLOT(actionPageDown()));
//    dockWidgetPageProperty->hide();
}

void MainWindow::rightDockWidgetCreate()
{
    dockWidgetPropertyShow = new QDockWidget(tr("属性"),this);
    dockWidgetPropertyShow->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidgetPropertyShow->setFeatures(QDockWidget::DockWidgetMovable);
    this->addDockWidget(Qt::RightDockWidgetArea,dockWidgetPropertyShow);
    QMainWindow *property = new QMainWindow;
    dockWidgetPropertyShow->setWidget(property);
    propertyShow = new QStackedWidget;
    property->setCentralWidget(propertyShow);
    //主页面信息
    QWidget * pageWidget = new QWidget;
    QLabel * currentIndex = new QLabel(tr("当前页数"),pageWidget);
    lableCurrentIndex = new QLabel;
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(currentIndex);
    hLayout->addWidget(lableCurrentIndex);
    pageWidget->setLayout(hLayout);
    propertyShow->addWidget(pageWidget);
    //按键信息页
    btnPropertyShow = new BtnPropertyShow;
    propertyShow->addWidget(btnPropertyShow);
//    dockWidgetPropertyShow->hide();
}

void MainWindow::dataInit()
{
    m_pageSum = 0;
    m_selectedPageNum = 0;
}

//第一行工具栏 新建工程
void MainWindow::actionNewProject()
{
    QFileInfo  fileInfo = QFileDialog::getSaveFileName(this,tr("请选择保存路径"),"GKprj.hmi","GKHMI(*.hmi)");
    if(fileInfo.filePath().isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("没有完成新建!"));
    }
    else
    {
        m_prjFileInfo = fileInfo;
//        removeFolderContent(fileInfo.path());
        QSettings *prj = new QSettings(m_prjFileInfo.filePath(),QSettings::IniFormat);
        prj->setValue("INIT/SIZE","800*480");
        prj->setValue("IMG/00",0);
        delete prj;

        newDir.mkdir("setUp");
        newDir.mkdir("background");
        newDir.mkdir("keyboard");
        newDir.mkdir("labTimeBack");
        newDir.mkdir("messageBox");
        QSettings *conf = new QSettings(m_prjFileInfo.path() + "/setUp/config.ini",QSettings::IniFormat);
        conf->setValue("PAGE/pageSum",0);
        conf->setValue("serial/dev","ttyS1");
        conf->setValue("serial/baud",9600);
        conf->setValue("serial/parity","n");
        delete conf;
        dockWidgetPropertyShow->show();
        dockWidgetPageProperty->show();
        tabWidget->setCurrentIndex(1);
    }
}

void MainWindow::actionOpenProject()
{
    QFileInfo  fileInfo = QFileDialog::getOpenFileName(this,tr("请选择工程"),"GKprj.hmi","GKHMI(*.hmi)");
    if(fileInfo.filePath().isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("选择失败!"));
    }
    else
    {
        m_prjFileInfo = fileInfo;
        QSettings *conf = new QSettings(m_prjFileInfo.path() + "/setUp/config.ini",QSettings::IniFormat);
        m_pageSum = conf->value("PAGE/pageSum").toInt();
        delete conf;

        for(int i=0;i< m_pageSum;i++)
        {
            m_background.insert(i,tr("%1.bmp").arg(i));
            pageTableWidget->insertRow(i);
            pageTableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
            pageTableWidget->setItem(i,1,new QTableWidgetItem(m_background.value(i)));

            newOnePage(i);
        }
        emit signalOpenAllItemConfig(m_prjFileInfo.path());
    }
}

void MainWindow::slotSaveProject()
{
    QSettings *conf = new QSettings(m_prjFileInfo.path() + "/setUp/config.ini",QSettings::IniFormat);
    conf->setValue("PAGE/pageSum",m_pageSum);
    delete conf;
    emit signalSaveAllItemToConfig(m_prjFileInfo.path());
}

void MainWindow::actionSetProject()
{
    ComSet *comSet = new ComSet;
    comSet->setSavePath(m_prjFileInfo.path() + "/setUp/config.ini");
    comSet->exec();
}

void MainWindow::slotDrawBtnTriggered()
{
    if(!sceneList.isEmpty())
    sceneList.at(m_selectedPageNum)->setItemType(BTN);
}
void MainWindow::slotDrawLabTrigger()
{
    if(!sceneList.isEmpty())
    sceneList.at(m_selectedPageNum)->setItemType(LABEL);
}


void MainWindow::newOnePage()
{
    QWidget *page = new QWidget(stackedView);
    pageList.append(page);
    stackedView->addWidget(page);
    int w =static_cast< QWidget *>(stackedView)->size().width();
    int h =static_cast< QWidget *>(stackedView)->size().height();
    myScene *pageScene = new myScene(page);
    sceneList.append(pageScene);
    pageScene->setScenePageIndex(m_pageSum);
    pageScene->setSceneRect(QRectF(0,0,w,h));
    QGraphicsView * pageView_0 = new QGraphicsView(pageScene,page);
    viewList.append(pageView_0);
    pageView_0->resize(QSize(800,480));
    pageView_0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->centerOn(0,0);
    pageView_0->show();
    connect(btnPropertyShow,SIGNAL(signalSendBtnInfoToScene(BTN_INFO)),pageScene,SLOT(slotGetBtnInfoChangedFromShow(BTN_INFO)));
    connect(btnPropertyShow,SIGNAL(signalSendBtnRectChanged(QRectF)),pageScene,SLOT(slotSelectRectChangedByShow(QRectF)));
    connect(pageScene,SIGNAL(signalSendBtnInfoToBtnShow(BTN_INFO *)),btnPropertyShow,SLOT(slotGetBtnInfoFromScene(BTN_INFO*)));
    connect(pageScene,SIGNAL(signalSendBtnItemQRectF(QRectF)),btnPropertyShow,SLOT(slotGetBtnItemQRectF(QRectF)));
    connect(pageScene,SIGNAL(signalSendWhichItemHasSelected(PROPERETY_SHOW_INDEX)),this,SLOT(slotGetWhichItemHasSelected(PROPERETY_SHOW_INDEX)));
    connect(this,SIGNAL(signalSaveAllItemToConfig(QString)),pageScene,SLOT(slotSaveAllItemOnScene(QString)));
}

void MainWindow::newOnePage(int index)
{
    QWidget *page = new QWidget(stackedView);
    pageList.append(page);
    stackedView->addWidget(page);
    int w =static_cast< QWidget *>(stackedView)->size().width();
    int h =static_cast< QWidget *>(stackedView)->size().height();
    myScene *pageScene = new myScene(page);
    sceneList.append(pageScene);
    pageScene->setScenePageIndex(index);
    pageScene->setSceneRect(QRectF(0,0,w,h));
    QGraphicsView * pageView_0 = new QGraphicsView(pageScene,page);
    viewList.append(pageView_0);
    pageView_0->resize(QSize(800,480));
    pageView_0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->centerOn(0,0);
    pageView_0->show();
    connect(btnPropertyShow,SIGNAL(signalSendBtnInfoToScene(BTN_INFO)),pageScene,SLOT(slotGetBtnInfoChangedFromShow(BTN_INFO)));
    connect(btnPropertyShow,SIGNAL(signalSendBtnRectChanged(QRectF)),pageScene,SLOT(slotSelectRectChangedByShow(QRectF)));
    connect(pageScene,SIGNAL(signalSendBtnInfoToBtnShow(BTN_INFO *)),btnPropertyShow,SLOT(slotGetBtnInfoFromScene(BTN_INFO*)));
    connect(pageScene,SIGNAL(signalSendBtnItemQRectF(QRectF)),btnPropertyShow,SLOT(slotGetBtnItemQRectF(QRectF)));
    connect(pageScene,SIGNAL(signalSendWhichItemHasSelected(PROPERETY_SHOW_INDEX)),this,SLOT(slotGetWhichItemHasSelected(PROPERETY_SHOW_INDEX)));
    connect(this,SIGNAL(signalSaveAllItemToConfig(QString)),pageScene,SLOT(slotSaveAllItemOnScene(QString)));
    connect(this,SIGNAL(signalOpenAllItemConfig(QString)),pageScene,SLOT(slotOpenReadAllItemOnScene(QString)));
    connect(this,SIGNAL(signalDeleteSelectedItemToScene(PROPERETY_SHOW_INDEX)),pageScene,SLOT(slotGetDeleteSelectedItemFromUI(PROPERETY_SHOW_INDEX)));
}

void MainWindow::actionNewPage()
{
    QFileInfo fileInfo =  QFileDialog::getOpenFileName(this,tr("请选择图片"),"","image file(*.bmp)");
    if(fileInfo.filePath().isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("选择失败!"));
    }
    else
    {
//        QFileInfo targetFile(m_prjFileInfo.path() + "/background/" +fileInfo.fileName());
//        QFile::copy(fileInfo.filePath(), targetFile.filePath());
        //将页码背景图 改为页码.bmp pageSum 等于当前增加页的值 当前页的值从0 开始
        QFileInfo targetFile(m_prjFileInfo.path() + tr("/background/%1.bmp").arg(m_pageSum));
        QFile::copy(fileInfo.filePath(), targetFile.filePath());

        m_background.insert(m_pageSum,targetFile.fileName());
        pageTableWidget->insertRow(m_pageSum);
        pageTableWidget->setItem(m_pageSum,0,new QTableWidgetItem(QString::number(m_pageSum)));
        pageTableWidget->setItem(m_pageSum,1,new QTableWidgetItem(m_background.value(m_pageSum)));
        m_selectedPageNum = m_pageSum;

        //new the page_? folder
        QDir newDir(m_prjFileInfo.path());
        newDir.mkdir(tr("page%1").arg(m_pageSum));
        newOnePage();
        m_pageSum ++;// pageSum 等于当前增加页的值 当前页的值从0 开始
    }
}

void MainWindow::actionDeleteOnePage()
{
    m_selectedPageNum = pageTableWidget->currentRow();
    qDebug()<<"m_selectedPageNum"<<m_selectedPageNum;
    sceneList.removeAt(m_selectedPageNum);
    viewList.removeAt(m_selectedPageNum);
    stackedView->removeWidget(pageList.at(m_selectedPageNum));
    pageList.removeAt(m_selectedPageNum);
//    pageTableWidget->removeRow(m_selectedPageNum);
}

void MainWindow::actionDeleteAllPage()
{

}

void MainWindow::actionPageUp()
{

}

void MainWindow::actionPageDown()
{

}

void MainWindow::slotPageTableWidgetSelectedChanged()
{
    sceneList.at(m_selectedPageNum)->clearAllItemSelected();//before the m_selected changed
    m_selectedPageNum = pageTableWidget->currentRow();
    lableCurrentIndex->setText(QString::number(m_selectedPageNum));
    stackedView->setCurrentIndex(m_selectedPageNum);
    viewList.at(m_selectedPageNum)->setStyleSheet(tr("background-image:url(%1/background/%2)")
                                                  .arg(m_prjFileInfo.path())
                                                  .arg(m_background.value(m_selectedPageNum)));
    //read current page item info and show in this page
}

void MainWindow::slotGetWhichItemHasSelected(PROPERETY_SHOW_INDEX index)
{
    propertyShow->setCurrentIndex(index);
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
    if(key->key()== Qt::Key_Delete)
    {
        qDebug()<<"delecte press";
        PROPERETY_SHOW_INDEX index = (PROPERETY_SHOW_INDEX) propertyShow->currentIndex();
        emit signalDeleteSelectedItemToScene(index);
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    qDebug()<<"doubule click";
    QMenu *menu = new QMenu;
    menu->show();
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    QString size;
    size = tr("this pos is %1,%2").arg(ev->pos().x()).arg(ev->pos().y());
//    this->setToolTip(size);
}

bool MainWindow::removeFolderContent(const QString &folderDir)
{
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return false;}//文件不存，则返回false
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0)
    {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--)
        {
            curFile=fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0)//下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j=0;j<fileList1.size();j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    return true;
}
