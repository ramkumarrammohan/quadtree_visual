#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "quadtree.h"

//class Quadtree;
//class Boundary;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QPainter *_painter = nullptr;
    bool _paint = false;
    bool _quadCreated = false;
    int m_boundWidth = 0;
    int m_boundHeight = 0;
    Boundary *_bound = nullptr;
    Quadtree *_quadtree = nullptr;

    void insertPoints();
};

#endif // MAINWINDOW_H
