#include <QCoreApplication>
#include <iostream>
#include <QTimer>
#include <QRandomGenerator>
#include <QPointF>
#include <QFile>
#include <QDir>
#include "SemiCL6Func.h"
//#include <QMessageBox>

using std::cout, std::endl;

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;
typedef QHash<QString, DataTable> FigureData;

DataTable generateRandomData(int listCount, int valueMax, int valueCount);
FigureData generateFigureData();
void saveCsvFileTable(QString sPathName, QString sFileName, DataTable& dt);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str = "Hello";
    cout << "abc123" << endl;
    cout << str.toStdString().data() << endl;

    //test function
    //DataTable mdt = generateRandomData(5, 10, 120);
    FigureData fhash = generateFigureData();
    //DataTable fdt = fhash["figure1"];
    /*
    qDebug() << "list count:" << fdt.count();
    qDebug() << "elem num in list0:" << fdt.at(0).count();
    qDebug() << fdt.at(0).at(0).first;
    qDebug() << fdt.at(0).at(0).second;
    qDebug() << fdt.at(0).at(1).first;
    qDebug() << fdt.at(0).at(1).second;

    int row, col;
    row = fdt.at(0).count();
    col = fdt.count(); //how many lists, there is how many cols
    QFile file;
    QString fileName;
    QString cPath;
    QString filePathName;
    cPath = QDir::currentPath();
    fileName = "figure1";

    filePathName = cPath + "/projdata/" +
               fileName + ".csv";
    qDebug() << filePathName;
    */
    //QDateTime current_datetime = QDateTime::currentDateTime();
    //QString Scurrent_datetime = current_datetime.toString("yyyy_MM_dd_hh_mm_ss");
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Excel file"), qApp->applicationDirPath (), tr("Files (*.csv)"));
    /*
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("保存表格"),
                                            QDir::currentPath() + "/" +\
                                                                       ui->lineEdit->text() + ".csv",
                                            tr("csv File(*.csv)"));
    if(fileName.isNull())
    {
        return;
    }
    */

    //file.exists() --return bool value indicate the file exist or not
    /*
    file.setFileName(filePathName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){  //QIODevice::Append indicate append data
        QTextStream out(&file);
        //不写表头
        for(int i(0); i<row; i++){
            out << fdt.at(0).at(i).first.x() << ",";  //to get x(), fix fetch the first col
            for(int j(0); j<col; j++){
                if(j==(col-1))
                    out << fdt.at(j).at(i).first.y() << "\n";   //after last col, there is no comma
                else
                    out << fdt.at(j).at(i).first.y() << ",";
            }
        }
        file.close();

    }
    qDebug() << "fdt.at(0).at(561).first.x()";
    qDebug() << fdt.at(0).at(561).first.x();
    qDebug() << fdt.at(0).at(561).first;
    */

    QString path(QDir::currentPath());
    path = path + "/projdata/";

    for(int i(1); i<=7; i++){
        saveCsvFileTable(path, "figure"+QString::number(i), fhash["figure"+QString::number(i)]);
    }


    //test end
    //Add this, otherwise the Qt console program will not end automatically
    QTimer t;
    t.connect(&t, SIGNAL(timeout()), &a, SLOT(quit()));
    t.start(5000);  // 5000millisecond

    return a.exec();
}

void saveCsvFileTable(QString sPathName, QString sFileName, DataTable& dt)  //sPathName must end of slash
{
    QDir dir(sPathName);
    if(!dir.exists())
        dir.mkdir(sPathName);
    QString filePathName = sPathName + sFileName + ".csv";
    QFile file;
    int row, col;
    row = dt.at(0).count();
    col = dt.count(); //how many lists, there is how many cols
    file.setFileName(filePathName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){  //QIODevice::Append indicate append data
        QTextStream out(&file);
        //no head of table
        for(int i(0); i<row; i++){
            out << dt.at(0).at(i).first.x() << ",";  //to get x(), fix fetch the first col
            for(int j(0); j<col; j++){
                if(dt.at(j).count()>i){  //figure6 last col only have 1 elem
                    if(j==(col-1))
                        out << dt.at(j).at(i).first.y() << "\n";   //after last col, there is no comma
                    else
                        out << dt.at(j).at(i).first.y() << ",";
                }
                else{
                    if(j==(col-1))
                        out << "\n";
                }
            }
        }
        file.close();
    }


}

FigureData generateFigureData(){
    FigureData datatableMap;
    if (!SemiCL6FuncInitialize()) // DLL Initialize
    {
        //QMessageBox msgBox;
        //msgBox.setText("SemiCL DLL initialization failed.");
        //msgBox.exec();
        qDebug("SemiCL DLL initialization failed.");
    }
    //figure1 array. num of rows and cols must pre define
    mwArray matrix_f1_x(1, 1120, mxDOUBLE_CLASS, mxREAL);    //first 2 param indicate rowCnt, colCnt. 1 row,1120 cols, store in col priority , also means 1 col, 1120 rows.
    mwArray matrix_f1_ph1(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph2(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph3(1, 1120, mxDOUBLE_CLASS, mxREAL);
    //figure2 array
    mwArray matrix_f2_x(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E1(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E2(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E3(1, 81, mxDOUBLE_CLASS, mxREAL);
    //figure3 array
    mwArray matrix_f3_x(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_HH1(1, 81, mxDOUBLE_CLASS, mxREAL);  //in matlab the array is 81*1, but use 1*81 there can still read the data
    mwArray matrix_f3_HH2(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_HH3(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_LH1(1, 81, mxDOUBLE_CLASS, mxREAL);
    //figure4 array
    mwArray matrix_f4_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f4_gai(1, 301, mxDOUBLE_CLASS, mxREAL);
    //figure5 array
    mwArray matrix_f5_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f5_ref(1, 301, mxDOUBLE_CLASS, mxREAL);
    //figure6 array
    mwArray matrix_f6_x(1, 9252, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f6_YYy(1, 9252, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f6_mm1(1, 1, mxDOUBLE_CLASS, mxREAL);
    //figure7 array
    mwArray matrix_f7_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f7_TT(1, 301, mxDOUBLE_CLASS, mxREAL);


    int nargout=22;  // the number of return params. must correct.
    SemiCL6Func(nargout,
                matrix_f1_x, matrix_f1_ph1, matrix_f1_ph2, matrix_f1_ph3,
                matrix_f2_x, matrix_f2_E1, matrix_f2_E2, matrix_f2_E3,
                matrix_f3_x, matrix_f3_HH1, matrix_f3_HH2, matrix_f3_HH3, matrix_f3_LH1,
                matrix_f4_x, matrix_f4_gai,
                matrix_f5_x, matrix_f5_ref,
                matrix_f6_x, matrix_f6_YYy, matrix_f6_mm1,
                matrix_f7_x, matrix_f7_TT
                );

    int listCount(0);
    int valueCount(0);

    //figure 1
    listCount = 3;
    valueCount = 1120;
    mwArray* f1_ph[3];
    f1_ph[0] = &matrix_f1_ph1;
    f1_ph[1] = &matrix_f1_ph2;
    f1_ph[2] = &matrix_f1_ph3;
    DataTable datatable_figure1;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f1_x.Get(1, j+1), f1_ph[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure1 << dataList;
    }
    datatableMap.insert("figure1", datatable_figure1);

    //figure 2
    mwArray* f2_E[3];
    f2_E[0] = &matrix_f2_E1;
    f2_E[1] = &matrix_f2_E2;
    f2_E[2] = &matrix_f2_E3;
    listCount = 3;
    valueCount = 81;
    DataTable datatable_figure2;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f2_x.Get(1, j+1), f2_E[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure2 << dataList;
    }
    datatableMap.insert("figure2", datatable_figure2);

    //figure 3
    mwArray* f3_p[4];
    f3_p[0] = &matrix_f3_HH1;
    f3_p[1] = &matrix_f3_HH2;
    f3_p[2] = &matrix_f3_HH3;
    f3_p[3] = &matrix_f3_LH1;
    listCount = 4;
    valueCount = 81;
    DataTable datatable_figure3;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f3_x.Get(1, j+1), f3_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure3 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert("figure3", datatable_figure3);

    //figure 4
    mwArray* f4_p[1];
    f4_p[0] = &matrix_f4_gai;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure4;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f4_x.Get(1, j+1), f4_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure4 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert("figure4", datatable_figure4);

    //figure 5
    mwArray* f5_p[1];
    f5_p[0] = &matrix_f5_ref;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure5;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f5_x.Get(1, j+1), f5_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure5 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert("figure5", datatable_figure5);

    //figure 6
    mwArray* f6_p[2];
    f6_p[0] = &matrix_f6_YYy;
    f6_p[1] = &matrix_f6_mm1;  //pass by a single number
    listCount = 2;
    valueCount = 9252;
    DataTable datatable_figure6;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        if(i < listCount-1){
            for (int j(0); j < valueCount; j++) {
                QPointF value(matrix_f6_x.Get(1, j+1), f6_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
                QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
                dataList << Data(value, label);
            }
        }
        else
        {
            //last datalist store a single number: matrix_f6_mm1
            for (int j(0); j < 1; j++) {  //j<1, indicate a single number
                QPointF value(0, f6_p[i]->Get(1, j+1)); //first param is not use. value.x() and value .y() can get two values
                QString label = "Slice " + QString::number(i) + ":" + "matrix_f6_mm1";
                dataList << Data(value, label);
            }
        }
        datatable_figure6 << dataList;
    }
    datatableMap.insert("figure6", datatable_figure6);

    //figure7
    mwArray* f7_p[1];
    f7_p[0] = &matrix_f7_TT;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure7;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f7_x.Get(1, j+1), f7_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure7 << dataList;
    }
    datatableMap.insert("figure7", datatable_figure7);

    return datatableMap;
}
