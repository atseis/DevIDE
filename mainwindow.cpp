#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QPushButton>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
#include<QTreeWidget>
#include<QTabBar>
#include<QCompleter>
#include<QFile>
#include<QString>
#include<QLineEdit>
#include<QDialog>
#include<QPushButton>
#include<QtGui>
#include<QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString curFile=ui->codeTab->currentFile();
    setWindowTitle(curFile);

    this->resize(QSize(800,500));//修改初始化窗口大小


    //=============================================设置treeView=========================================
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    dirModel->setRootPath(QDir::currentPath());
    dirModel->setNameFilters(QStringList() << "*.c" <<"*.cpp"<< "*.h"<<"*.txt");
//    dirModel->setNameFilterDisables(false);
    ui->treeView->setModel(dirModel);
    ui->treeView->setRootIndex(dirModel->index(QDir::currentPath()));
                // 只显示保留文件名
    for (int i = 1; i < dirModel->columnCount(); i++) {
        ui->treeView->hideColumn(i);
    }
    //-------------------------------------------------------------------------------------------------

    //my_tab->setShape(QTabBar::TriangularNorth);//设置显示样式
    //splitter();
    ui->splitter->setStretchFactor(0, 1);//初始左边占1/9
    ui->splitter->setStretchFactor(1, 8);//初始右边占8/9


    //查找功能
    findDlg = new QDialog(this);//创建一个对话框
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn= new QPushButton(tr("查找下一个"), findDlg);

    FindBack_CheckBox=new QCheckBox(tr("从后往前查找"));//从后往前查找
    FindWhole_CheckBox=new QCheckBox(tr("全词匹配"));//全词匹配
    FindCase_CheckBox=new QCheckBox(tr("区分大小写"));//区分大小写
/*
    QHBoxLayout *layout_0= new QHBoxLayout(findDlg);//将check框放在一起，水平排列
    layout_0->addWidget(FindBack_CheckBox);
    layout_0->addWidget(FindWhole_CheckBox);
    layout_0->addWidget(FindCase_CheckBox);
    */

    QVBoxLayout *layout_2= new QVBoxLayout(findDlg);//将一个行编辑器和一个按钮放到上面，并使用布局管理器进行布局。
    layout_2->addWidget(findLineEdit);
    layout_2->addWidget(FindBack_CheckBox);
    layout_2->addWidget(FindWhole_CheckBox);
    layout_2->addWidget(FindCase_CheckBox);
    layout_2->addWidget(btn);
    findDlg->setLayout(layout_2);

    connect(btn, SIGNAL(clicked()), this, SLOT(showFindText()));//将按钮的单击信号关联到自定义的显示查找到的文本槽上

    document=ui->codeTab->currentEditor()->document();//将文本编辑区转为QTextDocument对象
    row_num=document->lineCount();//获取行数
    row=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    ui->codeTab->newFile();
}


void MainWindow::on_action_Save_triggered()
{
    ui->codeTab->save();
}

void MainWindow::on_action_SaveAs_triggered()
{
    ui->codeTab->saveAs();
}

void MainWindow::on_action_open_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    // 如果文件名不为空，则加载文件
    if (!fileName.isEmpty()) {
        ui->codeTab->openFile(fileName);
        dirModel->setRootPath(QFileInfo(fileName).absolutePath());
        dirModel->setNameFilters(QStringList() << "*.c" <<"*.cpp"<< "*.h"<<"*.txt");
        ui->treeView->setModel(dirModel);
        ui->treeView->setRootIndex(dirModel->index(QFileInfo(fileName).absolutePath()));
                    // 只显示保留文件名
        for (int i = 1; i < dirModel->columnCount(); i++) {
            ui->treeView->hideColumn(i);
        }
    }
}

void MainWindow::on_action_open_files_triggered()
{
    QString directoryName = QFileDialog::getExistingDirectory(this,tr("选择文件夹"),".");

    if (!directoryName.isEmpty()){
        dirModel->setRootPath(directoryName);
        dirModel->setNameFilters(QStringList() << "*.c" <<"*.cpp"<< "*.h"<<"*.txt");
        ui->treeView->setModel(dirModel);
        ui->treeView->setRootIndex(dirModel->index(directoryName));
                    // 只显示保留文件名
        for (int i = 1; i < dirModel->columnCount(); i++) {
            ui->treeView->hideColumn(i);
        }
    }
}

void MainWindow::on_action_Close_triggered()
{
    if (ui->codeTab->maybeSave()) {
        ui->codeTab->removeTab(ui->codeTab->currentIndex());
    }
}

void MainWindow::on_action_Run_triggered()
{
    QString curFile=ui->codeTab->currentFile();

    QString dirName=QFileInfo(curFile).path();
    QString baseName=QFileInfo(curFile).baseName();
    QString suffix=QFileInfo(curFile).completeSuffix();
    QString fullName=QFileInfo(curFile).fileName();
    QString prefix;
    if(QString::compare(suffix,"cpp")==0)
        prefix="g++";
    else if(QString::compare(suffix,"c")==0)
        prefix="gcc";
    else {
        throw "FILE_SUFFIX_ERROR";
    }

    QString enterCmd="cd /d "+dirName;
    QString compileCmd=prefix+" -g "+fullName+" -o "+baseName+".exe";
    QString runCmd=baseName+".exe";

    QString cmd=enterCmd+" && "+compileCmd+" && "+runCmd;

    system(cmd.toStdString().c_str());
}

void MainWindow::on_action_Compile_triggered()
{
    QString curFile=ui->codeTab->currentFile();

    QString dirName=QFileInfo(curFile).path();
    QString baseName=QFileInfo(curFile).baseName();
    QString suffix=QFileInfo(curFile).completeSuffix();
    QString fullName=QFileInfo(curFile).fileName();
    QString prefix;
    if(QString::compare(suffix,"cpp")==0)
        prefix="g++";
    else if(QString::compare(suffix,"c")==0)
        prefix="gcc";
    else {
        throw "FILE_SUFFIX_ERROR";
    }

    QString enterCmd="cd /d "+dirName;
    QString compileCmd=prefix+" -g "+fullName+" -o "+baseName+".exe";
    QString cmd=enterCmd+" && "+compileCmd;
//    save();
    system(cmd.toStdString().c_str());
}


void MainWindow::showFindText()//在当前打开文本中查找
{
    QString str = findLineEdit->text();//获取行编辑器中要查找的字符串

    if(FindBack_CheckBox->isChecked()){
        if(FindWhole_CheckBox->isChecked()){
            if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively|QTextDocument::FindWholeWords))
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                   QMessageBox::warning(this, tr("查找"),
                            tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward|QTextDocument::FindWholeWords))
                {
                   QMessageBox::warning(this, tr("查找"),
                            tr("找不到%1").arg(str));
                }
            }
        }
        else if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively))
                {
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward))
                {
                   QMessageBox::warning(this, tr("查找"),
                            tr("找不到%1").arg(str));
                }
            }

    }
    else if(FindWhole_CheckBox->isChecked()){
            if(FindCase_CheckBox->isChecked()){//用来指定查找的方式。可以使用“|”符号来一起使用
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindCaseSensitively|QTextDocument::FindWholeWords))
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindWholeWords))
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
        }
        else if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindCaseSensitively))
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
}

void MainWindow::on_action_Find_triggered()//显示查找框
{
   findDlg->show();
   findDlg->setMinimumSize(320,235);
}

void MainWindow::on_action_visible_triggered()
{
    int j=0;
    for(int i=0;i<row_num;i++){//显示每一行
        //qDebug()<<i;
        QTextBlock oTextBlock = document->findBlockByNumber(i);
        oTextBlock.setVisible(true);
        for(;j<size;){//找到行注释和代码同时存在的一行，将行注释添加回去
            qDebug()<<zhushi_hang[j];
            if(i==zhushi_hang[j]){
                QString str="";
                str=daima[j]+zhushi[j];
                //将光标跳到指定行
                QTextCursor tc = ui->codeTab->currentEditor()->textCursor();
                int toPost =document->findBlockByNumber(i).position();
                tc.setPosition(toPost,QTextCursor::MoveAnchor);
                ui->codeTab->currentEditor()->setTextCursor(tc);
                //删除光标所在行
                tc.select(QTextCursor::BlockUnderCursor);
                tc.removeSelectedText();
                ui->codeTab->currentEditor()->insertPlainText("\n"+str);

                text.append(str);
                j++;
                break;
            }
            else{
                text.append(document->findBlockByLineNumber(i).text());//存到list中,用于之后的重写
                break;
            }
        }
    }

    //重写文件
    QString file= text.join("\n");//将QStringlist转化为QString

    //清空注释list和对应的int数组
    zhushi.clear();
    size=0;

    //调整与更新！！！！超重要！！！
    document->adjustSize();
    ui->codeTab->currentEditor()->update();
}
void MainWindow::on_action_unvisible_triggered()
{
    document = ui->codeTab->currentEditor()->document();//将文本编辑区转为QTextDocument对象
    row_num=document->lineCount();//获取行数
    qDebug()<<row_num;

    for(int i=0;i<row_num;i++){
        QString str = document->findBlockByLineNumber(i).text(); //获取第i行的内容

        if(str.contains("/*")){//如果包含“/*”(段落注释)字符串的话

            QString cur="/*";
            QString str_2=str.trimmed();//去掉字符串首尾空格
            int m=str_2.indexOf(cur);//返回在str中的索引下标
            QString ss=str.mid(0,m);//取代码部分
            if(m<1){
                int j=i;
                for(;j<row_num;j++){
                    QString str_j = document->findBlockByLineNumber(j).text(); //获取第j行的内容
                    if(str_j.contains("*/")){
                        break;
                    }
                }
                i=j;
                continue;
            }
        }
        QString cur="//";
        if(str.contains(cur)){//如果包含“//”字符串的话
            QString str_2=str.trimmed();//去掉字符串首尾空格
            if(str_2.startsWith("//")){//整行都是注释,直接隐藏掉这一行
                continue;
            }
            else {//把注释删掉并存起来
                int j=str.indexOf('/');//返回‘//’在str中的索引下标
                if(str.contains('"')){//有引号
                    QString a=str.mid(0,j);
                    QString b=str.mid(j);
                    if(a.contains('"')&&b.contains('"')){//注释在引号里面,作为字符串
                        int w=b.indexOf('"');
                        QString ww=b.mid(w);
                        if(ww.contains("//")){//引号后面有注释
                            int p=ww.indexOf('/');
                            QString ss=str.mid(0,p+j+w);//取代码部分
                            daima.append(ss);
                            QString s=str.mid(p+j+w);//取注释
                            zhushi.append(s);
                            zhushi_hang[size]=i;
                            size++;
                            //需要再把这一行更改后的结果重新写到textedit吗？？？？!!!!!需要!!!!

                            //将光标跳到指定行
                            QTextCursor tc = ui->codeTab->currentEditor()->textCursor();
                            int toPost =document->findBlockByNumber(i).position();
                            tc.setPosition(toPost,QTextCursor::MoveAnchor);
                            ui->codeTab->currentEditor()->setTextCursor(tc);
                            //删除光标所在行
                            tc.select(QTextCursor::BlockUnderCursor);
                            tc.removeSelectedText();
                            ui->codeTab->currentEditor()->insertPlainText("\n"+ss);
                        }
                    }
                    else {
                        QString ss=str.mid(0,j);//取代码部分
                        daima.append(ss);
                        QString s=str.mid(j);//取注释
                        zhushi.append(s);
                        zhushi_hang[size]=i;
                        size++;
                        //需要再把这一行更改后的结果重新写到textedit吗？？？？!!!!!需要!!!!

                        //将光标跳到指定行
                        QTextCursor tc = ui->codeTab->currentEditor()->textCursor();
                        int toPost =document->findBlockByNumber(i).position();
                        tc.setPosition(toPost,QTextCursor::MoveAnchor);
                        ui->codeTab->currentEditor()->setTextCursor(tc);
                        //删除光标所在行
                        tc.select(QTextCursor::BlockUnderCursor);
                        tc.removeSelectedText();
                        ui->codeTab->currentEditor()->insertPlainText("\n"+ss);
                    }
                }
                else{//整行无引号
                    QString ss=str.mid(0,j);//取代码部分
                    daima.append(ss);
                    QString s=str.mid(j);//取注释
                    zhushi.append(s);
                    zhushi_hang[size]=i;
                    size++;
                    //需要再把这一行更改后的结果重新写到textedit吗？？？？!!!!!需要!!!!

                    //将光标跳到指定行
                    QTextCursor tc = ui->codeTab->currentEditor()->textCursor();
                    int toPost =document->findBlockByNumber(i).position();
                    tc.setPosition(toPost,QTextCursor::MoveAnchor);
                    ui->codeTab->currentEditor()->setTextCursor(tc);
                    //删除光标所在行
                    tc.select(QTextCursor::BlockUnderCursor);
                    tc.removeSelectedText();
                    ui->codeTab->currentEditor()->insertPlainText("\n"+ss);
                }
            }
        }
    }
    for(int i=0;i<row_num;i++){
        QString str = document->findBlockByLineNumber(i).text(); //获取第i行的内容
        if(str.contains("/*")){//如果包含“/*”(段落注释)字符串的话
            if(str.contains("*/")){
                int jj=str.indexOf("*/");//返回‘*/’在str中的索引下标
                QString q=str.mid(0,str.indexOf("/*"));
                QString p=str.mid(jj);
                if(q.contains('"')&&p.contains('"'));
                else{
                    QString cur="/*";
                    QString str_2=str.trimmed();//去掉字符串首尾空格
                    int m=str_2.indexOf(cur);//返回在str中的索引下标
                    if(m<1){
                        int j=i;
                        for(;j<row_num;j++){
                            QString str_j = document->findBlockByLineNumber(j).text(); //获取第j行的内容
                            if(str_j.contains("*/")){
                                break;
                            }
                        }
                        for(int mm=i;mm<=j;mm++){//隐掉段落注释
                            QTextBlock oTextBlock = document->findBlockByNumber(mm);
                            oTextBlock.setVisible(false);
                        }
                        i=j;
                        continue;
                    }
                }
            }
            else{
                QString cur="/*";
                QString str_2=str.trimmed();//去掉字符串首尾空格
                int m=str_2.indexOf(cur);//返回在str中的索引下标
                if(m<1){
                    int j=i;
                    for(;j<row_num;j++){
                        QString str_j = document->findBlockByLineNumber(j).text(); //获取第j行的内容
                        if(str_j.contains("*/")){
                            break;
                        }
                    }
                    for(int mm=i;mm<=j;mm++){//隐掉段落注释
                        QTextBlock oTextBlock = document->findBlockByNumber(mm);
                        oTextBlock.setVisible(false);
                    }
                    i=j;
                    continue;
                }
            }
        }
        if(str.contains("//")){//如果包含“//”字符串的话
            QString str_2=str.trimmed();//去掉字符串首尾空格
            if(str_2.startsWith("//")){//整行都是注释,直接隐藏掉这一行
                QTextBlock oTextBlock = document->findBlockByNumber(i);
                oTextBlock.setVisible(false);
            }
        }
    }
    //调整与更新！！！！超重要！！！
    document->adjustSize();
    ui->codeTab->currentEditor()->update();
}

void MainWindow::on_action_wh_v_triggered(){//while循环的显示
    for(int i=0;i<row_num;i++){//显示每一行
        QTextBlock oTextBlock = document->findBlockByNumber(i);
        oTextBlock.setVisible(true);
    }
    document->adjustSize();
    ui->codeTab->currentEditor()->update();
}
void MainWindow::on_action_wh_unv_triggered(){//while循环的隐藏
    document = ui->codeTab->currentEditor()->document();//将文本编辑区转为QTextDocument对象
    row_num=document->lineCount();//获取行数

    int zuo=0;
    int you=0;
    int a[10000];
    int count=0;
    int flag=0;//用来判断是不是while循环
    int ff=0;//用来判断是不是第一个括号

    for(int i=0;i<row_num;i++){
        QString str = document->findBlockByLineNumber(i).text(); //获取第i行的内容

        if(str.contains("while")&&(!str.contains('"'))&&(!str.contains("//"))){//如果包含while的话
            flag=1;
            if(str.contains('{')){
                zuo++;
                ff=1;
            }
        }
        else{
            if(flag==1){
                if(str.contains('{')){
                    zuo++;
                }
                if(str.contains('}')){
                    you++;
                }
                if(zuo>you){
                    if(zuo==1&&ff==0){//第一个括号不能隐藏
                        ff=1;
                    }
                    else{
                        a[count]=i;
                        count++;
                    }
                }
                if(zuo==you){
                    zuo=0;
                    you=0;
                    flag=0;
                    ff=0;
                    int jj=i+1;
                    if(jj<row_num){
                        while(jj<row_num){
                            QString str = document->findBlockByLineNumber(jj).text(); //获取第i行的内容
                            if(str.contains("while")&&!str.contains('"')&&(!str.contains("//"))){
                                i=jj-1;
                                flag=1;
                                break;
                            }
                            else{
                                jj++;
                            }
                        }
                        if(jj>=row_num){
                            i=row_num-1;
                            break;
                        }
                    }
                }
            }

        }
    }
    for(int i=0;i<count;i++){
        QTextBlock oTextBlock = document->findBlockByNumber(a[i]);
        oTextBlock.setVisible(false);
    }
    document->adjustSize();
    ui->codeTab->currentEditor()->update();
}


/*
void MainWindow::splitter(){
    QSplitter * mainSplitter = new QSplitter(Qt::Horizontal,ui->centralWidget);
    mainSplitter->setHandleWidth(3);//设置分割条宽度
    mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式

    mainSplitter->addWidget(ui->treeWidget);
    mainSplitter->addWidget(ui->codeTab->currentEditor());
    mainSplitter->setOrientation(Qt::Vertical);//指定子窗件按加载顺序进行指定方向排列
    mainSplitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainSplitter->show();
}
*/

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->codeTab->openFile(path);
}
