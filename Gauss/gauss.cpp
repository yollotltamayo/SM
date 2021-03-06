#include "gauss.h"
#include "ui_gauss.h"
#include <QStandardItemModel>
#include <QMessageBox>

gauss::gauss(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gauss)
{
    ui->setupUi(this);
    mGauss = new QStandardItemModel(this);
    mResp = new QStandardItemModel(this);
    ui->tableView->setModel(mGauss);
      ui->tableView_2->setModel(mResp);
      n = 3;
      ui->spinBox->setValue(3);
}

gauss::~gauss()
{
    delete ui;
}
void gauss::get()
{
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n+1;j++)
         {
              a[i][j] = getValueAt(mGauss,i,j);
         }
    }
}

void gauss::gausss()//converting augmented matrix to row echelon form
    {
        double temp;//Line 1
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                temp=a[j][i]/a[i][i];//Line 2
                for(int k=i;k<n+1;k++)
                {
                      a[j][k]-=temp*a[i][k];//Line 3
                    //a[j][k]-=a[j][i]*a[i][k]/a[i][i];//Line 4
                }
            }
        }
    }
void gauss::on_pushButton_clicked()
{
    menuSEL *ventana = new menuSEL;
    ventana->setVisible(true);
    this->setVisible(false);
}
void gauss::EnterJordan()//converting to reduced row echelon form
   {
      double temp;
       for(int i=n-1;i>=0;i--)
       {

           for(int j=i-1;j>=0;j--)
           {
               temp= a[j][i]/a[i][i];
               for(int k=n;k>=i;k--)
               {
                   a[j][k]-=temp*a[i][k];
               }
           }
       }

       double x[n];
       for(int i=0;i<n;i++)//making leading coefficients zero
           x[i]=0;
       for(int i=0;i<n;i++)
       {
           for(int j=0;j<n+1;j++)
           {
               if(x[i] == 0.0&&j!=n)
                   x[i]=a[i][j];
               if(x[i] != 0.0)
                   a[i][j]/=x[i];
           }
       }
   }

void gauss::on_spinBox_valueChanged(int arg1)
{
    n = arg1;
}
double gauss::getValueAt(QStandardItemModel *model, int fila, int col) const
{
    auto item = model->item(fila,col);
    if(!item)
    {
        return 0.0;
    }
    return item->text().toDouble();
}
void gauss::on_pushButton_3_clicked(){
    mGauss->setColumnCount(n+1);
    mGauss->setRowCount(n);
    mResp->setColumnCount(2);
    mResp->setRowCount(n);
}

void gauss::on_pushButton_2_clicked()
{
    mGauss->setColumnCount(n+1);
    mGauss->setRowCount(n);
    mResp->setColumnCount(2);
    mResp->setRowCount(n);
    get();
    gausss();
    EnterJordan();
    QString p = "x";
    for(int z = 0;z<n;z++)
    {  p.append(QString::number(z));
       mResp->setItem(z,0,new QStandardItem(p));
    p= "x" ;
    }
    for(int i=0;i<n;i++)
        mResp->setItem(i,1,new QStandardItem(QString::number(a[i][n])));
}

