#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>

#include "quadtree.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (_paint)
    {
        _quadtree->show(&painter);
        Boundary boundary(148, 150, 102, 102);

        QPen pen;
        pen.setColor("green");
        painter.setPen(pen);
        painter.drawRect(QRect(boundary.m_x - boundary.m_w,
                               boundary.m_y - boundary.m_h,
                               boundary.m_w * 2,
                               boundary.m_h * 2));

        std::vector<Point*> points;
        _quadtree->query(&boundary, &points);
        qDebug() << "count: " << points.size();

        foreach (Point *p, points) {
            pen.setColor("green");
            pen.setWidth(4);
            painter.setPen(pen);
            painter.drawPoint(p->x(), p->y());
        }
        _paint = false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (!_quadCreated)
    {
        m_boundWidth = ui->centralWidget->width() / 2;
        m_boundHeight = ui->centralWidget->height() / 2;

        _bound = new Boundary(m_boundWidth, m_boundHeight,
                              m_boundWidth, m_boundHeight);
        _quadtree = new Quadtree(_bound);
        _quadCreated = true;
    }

    Point *point = nullptr;
    for (int i = 0; i < 400; i++)
    {
        point = new Point(rand() % ui->centralWidget->width(),
                          rand() % ui->centralWidget->height());
        _quadtree->insert(point);
    }
    _paint = true;
    update();
}
