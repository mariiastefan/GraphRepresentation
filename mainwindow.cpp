#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "graf.h"
#include "arc.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QWidget>
#include <QRadioButton>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
#include <stddef.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawNode = false;
    drawArc = false;
    isOriented = false;
    ui->setupUi(this);
      m_button = new QPushButton("Afisare matrice", this);
      m_button->setGeometry(QRect(QPoint(50, 50), QSize(200, 50)));
      connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);


}

void MainWindow::handleButton()
{
  m_button->setText("Verificati fisier");
  QFile fil("D:/AG/tema1/matr_ad.txt");
  if(fil.open(QIODevice::WriteOnly | QIODevice::Text))
  {
      QTextStream stream(&fil);
      std::vector<Arc> gf;
      int **matr;
      matr=new int*[g.getNumberofNodes()];
       for(int index=0;index<g.getNumberofNodes();index++)
           matr[index]=new int[g.getNumberofNodes()];
      gf=g.GetArce();
      for(int index=0;index<g.getNumberofNodes();index++)
         {
          for(int index1=0;index1<g.getNumberofNodes();index1++)
             matr[index][index1]=0;
         }
      for(auto index:gf)
      {
          matr[index.getFirstPoint().getNumber()][index.getSecondPoint().getNumber()]=1;
          matr[index.getSecondPoint().getNumber()][index.getFirstPoint().getNumber()]=1;
      }
      for(int index=0;index<g.getNumberofNodes();index++)
         {
          for(int index1=0;index1<g.getNumberofNodes();index1++)
             { stream<<matr[index][index1]<<" ";
          }
          stream<<"\n";

      }


fil.close();
  }
  m_button->resize(100,100);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    drawNode = false;
    drawArc = false;
    if(e->button() == Qt::RightButton)
    {
        Node n(e->pos());
        std::vector<Node> noduri;
        noduri=g.GetNoduri();
        for(auto index:noduri)
        {
                if(fabs(index.getPoint().rx()-e->pos().rx())<20 && fabs(index.getPoint().ry()-e->pos().ry())<20 )
        {
               return;
        }
        }
        {
         g.AddNod(n);
        drawNode = true;
        update();
        firstNode = Node();
        }
    }
    else
    {
        QPointF p = e->localPos();
        std::vector<Node> noduri = g.GetNoduri();
        Node foundNode;
        for (auto& n : noduri)
        {
            if (fabs(n.getPoint().x() - p.x()) < 20 && fabs(n.getPoint().y() - p.y()) < 20)
            {
                foundNode = n;
                break;
            }
        }
        if (foundNode.getNumber() == -1)
            return;
        if (firstNode.getNumber() == -1)
        {
            firstNode = foundNode;
        }
        else
        {

            secondNode = foundNode;
            g.AddArc(Arc(firstNode, secondNode));
            firstNode = Node();
            secondNode = Node();
            drawArc = true;
            update();
        }
    }

}
void Sageata(QPainter& painter, QPoint start, QPoint end) {

  painter.setRenderHint(QPainter::Antialiasing, true);

  qreal arrowSize = 20;
  painter.setPen(Qt::green);
  painter.setBrush(Qt::green);

  QLineF line(end, start);

  double angle = std::atan2(-line.dy(), line.dx());
  QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

  QPolygonF arrowHead;
  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;
  painter.drawLine(line);
  painter.drawPolygon(arrowHead);

}
void MainWindow::paintEvent(QPaintEvent *event)
{


    if (g.getNumberofNodes())
    {
        QPainter p(this);
        std::vector<Node> noduri = g.GetNoduri();
        for(auto& nod: noduri)
        {
            QRect r(nod.getPoint().x()-10,nod.getPoint().y()-10, 20,20);
            p.drawEllipse(r);
            p.drawText(nod.getPoint(), QString::number(nod.getNumber()));
        }
       /* std::vector<Arc> arce = g.GetArce();
        for(auto& arc: arce)
        {
            p.drawLine(arc.getFirstPoint().getPoint(), arc.getSecondPoint().getPoint());

        }*/
        std::vector<Arc> arce1 = g.GetArce();
               for(auto& ind: arce1)
               {
                   if(isOriented == true)
                   {
                           Sageata(p, ind.getFirstPoint().getPoint(), ind.getSecondPoint().getPoint());
                   }
                   else p.drawLine(ind.getFirstPoint().getPoint(), ind.getSecondPoint().getPoint());
               }
        if (drawNode)
        {
            Node n = g.GetLastNode();
           p.setPen(QPen(Qt::blue));
            QRect r(n.getPoint().x()-10,n.getPoint().y()-10, 20,20);
            p.drawEllipse(r);
            p.drawText(n.getPoint(), QString::number(n.getNumber()));
        }
        else if (drawArc)
        {
            p.setPen(QPen(Qt::green));
            p.drawLine(QLine(arce1[arce1.size()-1].getFirstPoint().getPoint(), arce1[arce1.size()-1].getSecondPoint().getPoint()));
        }
    }
}



MainWindow::~MainWindow()
{
    QFile file("D:/AG/tema1/lista_adiac.txt");
          if(file.open(QIODevice::WriteOnly | QIODevice::Text))
          {
              QTextStream stream(&file);
              std::vector<Arc> gf;
              gf=g.GetArce();
              for(auto index:gf)
                 stream<<index.getFirstPoint().getNumber()<<" "<<index.getSecondPoint().getNumber()<<"\n";
              file.close();
          }
    if(isOriented==false)
    {
        QFile fil("D:/AG/tema1/matr_ad.txt");
        if(fil.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&fil);
            std::vector<Arc> gf;
            int **matr;
            matr=new int*[g.getNumberofNodes()];
             for(int index=0;index<g.getNumberofNodes();index++)
                 matr[index]=new int[g.getNumberofNodes()];
            gf=g.GetArce();
            for(int index=0;index<g.getNumberofNodes();index++)
               {
                for(int index1=0;index1<g.getNumberofNodes();index1++)
                   matr[index][index1]=0;
               }
            for(auto index:gf)
            {
                matr[index.getFirstPoint().getNumber()][index.getSecondPoint().getNumber()]=1;
                matr[index.getSecondPoint().getNumber()][index.getFirstPoint().getNumber()]=1;
            }
            for(int index=0;index<g.getNumberofNodes();index++)
               {
                for(int index1=0;index1<g.getNumberofNodes();index1++)
                   { stream<<matr[index][index1]<<" ";
                }
                stream<<"\n";
            }
      fil.close();
    }
    }
     if(isOriented==true)
     {
         QFile fil("D:/AG/tema1/matr_ad.txt");
         if(fil.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             QTextStream stream(&fil);
             std::vector<Arc> gf;
             int **matr;
             matr=new int*[g.getNumberofNodes()];
              for(int index=0;index<g.getNumberofNodes();index++)
                  matr[index]=new int[g.getNumberofNodes()];
             gf=g.GetArce();
             for(int index=0;index<g.getNumberofNodes();index++)
                {
                 for(int index1=0;index1<g.getNumberofNodes();index1++)
                    matr[index][index1]=0;
                }
             for(auto index:gf)
             {
                 matr[index.getFirstPoint().getNumber()][index.getSecondPoint().getNumber()]=1;
             }
             for(int index=0;index<g.getNumberofNodes();index++)
                {
                 for(int index1=0;index1<g.getNumberofNodes();index1++)
                    { stream<<matr[index][index1]<<" ";
                 }
                 stream<<"\n";
             }
       fil.close();
     }
     }

    delete ui;
}


void MainWindow::on_SaveGraf_released()
{

}


void MainWindow::on_Orientat_clicked()
{
    isOriented = true;
}


void MainWindow::on_Neorientat_clicked()
{
    isOriented = false;
}




void MainWindow::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        QMessageBox::information(this,"Ai ales","GrafOrientat");
        on_Orientat_clicked();
    }
    if(ui->radioButton_2->isChecked())
    {
        QMessageBox::information(this,"Ai ales","GrafNeorientat");
        on_Neorientat_clicked();

    }
}

