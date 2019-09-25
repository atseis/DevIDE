#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileInfoList>
#include <QTabBar>
#include <QSplitter>
#include <QDialog>
#include <QTextDocument>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

class QLineEdit;
class QDialog;
class QCheckBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString current_url;//当前打开文件夹路径
    QTabBar *my_tab=new QTabBar(this);//创建tabbar

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void splitter();//分割窗体

signals:
    void itemClicked ( QTreeWidgetItem * item, int column );//发射鼠标点击信号

private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Close_triggered();

    void on_action_Run_triggered();

    void on_action_Compile_triggered();


    void on_action_open_file_triggered();//打开单个文件

    void on_action_open_files_triggered();//打开文件夹

    void showFindText();//与查找信号连接的槽
    void on_action_Find_triggered();//与点击查找按钮或快捷键信号连接的槽

    void on_action_visible_triggered();//注释的显示
    void on_action_unvisible_triggered();//注释的隐藏

    void on_action_wh_v_triggered();//注释的显示
    void on_action_wh_unv_triggered();//注释的隐藏


    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel * dirModel;

    //为真：未保存过；为假：保存过
    bool isUntitled;
    //保存当前文件的路径
    QString curFile;

    QLineEdit *findLineEdit;
    QDialog *findDlg;

    QCheckBox *FindBack_CheckBox;//从后往前查找
    QCheckBox *FindWhole_CheckBox;//全词匹配
    QCheckBox *FindCase_CheckBox;//区分大小写

    QStringList zhushi;//存删掉的行注释(这一行还有代码)
    QStringList daima;//存删掉的行注释这一行的代码
    int zhushi_hang[2000];//存对应行注释的行数(限定2000行)
    int size=0;//数组大小

    QStringList text;//用于重写文件
    int row_num;//行数

    QTextDocument *document;

    int row;//记录隐藏掉的行数

};

#endif // MAINWINDOW_H
