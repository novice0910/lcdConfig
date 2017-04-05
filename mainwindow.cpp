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
    QAction *actionNewProject = new QAction(tr("新建"),this);
    actionNewProject->setToolTip(tr("新建工程"));
    connect(actionNewProject,SIGNAL(triggered()),this,SLOT(slotNewProject()));
    toolBarProject->addAction(actionNewProject);
    QAction *actionOpenProject = new QAction(tr("打开"),this);
    actionOpenProject->setToolTip(tr("打开工程"));
    connect(actionOpenProject,SIGNAL(triggered()),this,SLOT(slotOpenProject()));
    toolBarProject->addAction(actionOpenProject);
    QAction *actionSaveProject = new QAction(tr("Debug"),this);
    actionSaveProject->setToolTip(tr("生成配置文件"));
    connect(actionSaveProject,SIGNAL(triggered()),this,SLOT(slotSaveProject()));
    toolBarProject->addAction(actionSaveProject);
    QAction *actionSetProject = new QAction(tr("设置"),this);
    actionSetProject->setToolTip(tr("串口设置"));
    connect(actionSetProject,SIGNAL(triggered()),this,SLOT(slotSetProject()));
    toolBarProject->addAction(actionSetProject);
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
    QToolBar *pToolBar = leftDockMainwindow->addToolBar("new");
    pToolBar->addAction(tr("新增"),this,SLOT(slotActionNewPage()));
    pToolBar->addAction(tr("删除"),this,SLOT(slotActionNewPage()));
    pToolBar->addAction(tr("上移"),this,SLOT(slotActionNewPage()));
    pToolBar->addAction(tr("下移"),this,SLOT(slotActionNewPage()));
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
    m_pageSum = -1;
    m_selectedPageNum = 0;
}

//第一行工具栏
void MainWindow::slotNewProject()
{
    QFileInfo  fileInfo = QFileDialog::getSaveFileName(this,tr("请选择保存路径"),"GKprj.hmi","GKHMI(*.hmi)");
    if(fileInfo.filePath().isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("没有完成新建!"));
    }
    else
    {
        m_prjFileInfo = fileInfo;
        QSettings *prj = new QSettings(m_prjFileInfo.filePath(),QSettings::IniFormat);
        prj->setValue("INIT/SIZE","800*480");
        prj->setValue("IMG/00",0);
        delete prj;

        QDir newDir(m_prjFileInfo.path());
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

void MainWindow::slotOpenProject()
{
    QFileInfo  fileInfo = QFileDialog::getOpenFileName(this,tr("请选择工程"),"GKprj.hmi","GKHMI(*.hmi)");
    if(fileInfo.filePath().isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("选择失败!"));
    }
    else
    {
        m_prjFileInfo = fileInfo;
        emit signalOpenAllItemConfig(m_prjFileInfo.path());
        newOnePage();
    }
}

void MainWindow::slotSaveProject()
{
    QSettings *conf = new QSettings(m_prjFileInfo.path() + "/setUp/config.ini",QSettings::IniFormat);
    conf->setValue("PAGE/pageSum",m_pageSum + 1);
    delete conf;
    emit signalSaveAllItemToConfig(m_prjFileInfo.path());
}

void MainWindow::slotSetProject()
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

void MainWindow::deleteItem()
{
//    foreach (QGraphicsItem *item, scene->selectedItems()) {
//        if (item->type() == Arrow::Type) {
//            scene->removeItem(item);
//            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
//            arrow->startItem()->removeArrow(arrow);
//            arrow->endItem()->removeArrow(arrow);
//            delete item;
//        }
//    }

//    foreach (QGraphicsItem *item, scene->selectedItems()) {
//         if (item->type() == DiagramItem::Type) {
//             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
//         }
//         scene->removeItem(item);
//         delete item;
//     }
}
void MainWindow::slotItemHasInserted(myItem *item)
{
    Q_UNUSED(item);
    if(!sceneList.isEmpty())
    sceneList.at(m_selectedPageNum)->setItemType(MOVE_ITEM);
}

void MainWindow::slotGetBtnInfoFromScene(BTN_INFO * btn)
{
    Q_UNUSED(btn);
    propertyShow->setCurrentIndex(BTN_INDEX);
}

void MainWindow::slotActionNewPage()
{
    QFileInfo fileInfo =  QFileDialog::getOpenFileName(this,tr("请选择图片"),"","image file(*.bmp)");
    if(fileInfo.filePath().isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("选择失败!"));
    }
    else
    {
        QFileInfo targetFile(m_prjFileInfo.path() + "/background/" +fileInfo.fileName());
        QFile::copy(fileInfo.filePath(), targetFile.filePath());
        m_pageSum ++;
        m_background.insert(m_pageSum,targetFile.fileName());
        pageTableWidget->insertRow(m_pageSum);
        pageTableWidget->setItem(m_pageSum,0,new QTableWidgetItem(QString::number(m_pageSum)));
        pageTableWidget->setItem(m_pageSum,1,new QTableWidgetItem(m_background.value(m_pageSum)));
        m_selectedPageNum = m_pageSum;

        //new the page_? folder
        QDir newDir(m_prjFileInfo.path());
        newDir.mkdir(tr("page%1").arg(m_pageSum));

        newOnePage();
    }
}

void MainWindow::newOnePage()
{
    QWidget *page = new QWidget(stackedView);
    stackedView->addWidget(page);
    int w =static_cast< QWidget *>(stackedView)->size().width();
    int h =static_cast< QWidget *>(stackedView)->size().height();
    myScene *pageScene = new myScene(page);
    sceneList.append(pageScene);
    pageScene->setScenePageIndex(m_pageSum);
    pageScene->setSceneRect(QRectF(0,0,w,h));
    connect(pageScene,SIGNAL(signalItemHasInserted(myItem*)),this,SLOT(slotItemHasInserted(myItem*)));
    QGraphicsView * pageView_0 = new QGraphicsView(pageScene,page);
    viewList.append(pageView_0);
    pageView_0->resize(QSize(800,480));
    pageView_0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->centerOn(0,0);
    pageView_0->show();
    connect(btnPropertyShow,SIGNAL(signalSendBtnInfoToScene(BTN_INFO)),pageScene,SLOT(slotGetBtnInfoChanged(BTN_INFO)));
    connect(btnPropertyShow,SIGNAL(signalSendBtnRectChanged(QRectF)),pageScene,SLOT(slotSelectRectChanged(QRectF)));
    connect(pageScene,SIGNAL(signalSendBtnItemQRectF(QRectF)),btnPropertyShow,SLOT(slotGetBtnItemQRectF(QRectF)));
    connect(pageScene,SIGNAL(signalSendWhichItemHasSelected(PROPERETY_SHOW_INDEX)),this,SLOT(slotGetWhichItemHasSelected(PROPERETY_SHOW_INDEX)));
    connect(this,SIGNAL(signalSaveAllItemToConfig(QString)),pageScene,SLOT(slotSaveAllItemOnScene(QString)));
}

void MainWindow::newOnePage(int index)
{
    QWidget *page = new QWidget(stackedView);
    stackedView->addWidget(page);
    int w =static_cast< QWidget *>(stackedView)->size().width();
    int h =static_cast< QWidget *>(stackedView)->size().height();
    myScene *pageScene = new myScene(page);
    sceneList.append(pageScene);
    pageScene->setScenePageIndex(index);
    pageScene->setSceneRect(QRectF(0,0,w,h));
    connect(pageScene,SIGNAL(signalItemHasInserted(myItem*)),this,SLOT(slotItemHasInserted(myItem*)));
    QGraphicsView * pageView_0 = new QGraphicsView(pageScene,page);
    viewList.append(pageView_0);
    pageView_0->resize(QSize(800,480));
    pageView_0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageView_0->centerOn(0,0);
    pageView_0->show();
    connect(btnPropertyShow,SIGNAL(signalSendBtnInfoToScene(BTN_INFO)),pageScene,SLOT(slotGetBtnInfoChanged(BTN_INFO)));
    connect(btnPropertyShow,SIGNAL(signalSendBtnRectChanged(QRectF)),pageScene,SLOT(slotSelectRectChanged(QRectF)));
    connect(pageScene,SIGNAL(signalSendBtnItemQRectF(QRectF)),btnPropertyShow,SLOT(slotGetBtnItemQRectF(QRectF)));
    connect(pageScene,SIGNAL(signalSendWhichItemHasSelected(PROPERETY_SHOW_INDEX)),this,SLOT(slotGetWhichItemHasSelected(PROPERETY_SHOW_INDEX)));
    connect(this,SIGNAL(signalSaveAllItemToConfig(QString)),pageScene,SLOT(slotSaveAllItemOnScene(QString)));
}

void MainWindow::slotActionDeletePage()
{

}
void MainWindow::slotActionUp()
{

}
void MainWindow::slotActionDown()
{

}

void MainWindow::slotPageTableWidgetSelectedChanged()
{
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

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    qDebug()<<"doubule click";
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    QString size;
    size = tr("this pos is %1,%2").arg(ev->pos().x()).arg(ev->pos().y());
//    this->setToolTip(size);
}
