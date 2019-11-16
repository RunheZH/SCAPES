#include "../inc/tabchildwidget.h"
#include "./ui_tabchildwidget.h"

tabchildwidget::tabchildwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabchildwidget)
{
    ui->setupUi(this);
    //when user scroll textedit, the linenumber will also sync with the textedit scrollbar
    connect(ui->textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)),this,SLOT(updateScroll(int)));
}

tabchildwidget::~tabchildwidget()
{
    qDebug()<<"~tabchildwidget() -"<<fileName;
    delete ui;
}

void tabchildwidget::setText(QString text){
    ui->textEdit->setPlainText(text);
}

QString tabchildwidget::getText(){
    return ui->textEdit->toPlainText();
}

bool tabchildwidget::isEmpty(){
//    qDebug()<<ui->textEdit->document();
    if(ui->textEdit->document()->isEmpty()){
        return true;
    }else{
        return false;
    }
}

void tabchildwidget::clearText(){
    ui->textEdit->clear();
}

void tabchildwidget::storeFilePath(QString filePath){
    this->filePath = filePath;
}

QString tabchildwidget::getFilePath(){
    return filePath;
}

QString tabchildwidget::getFileName(){
    fileName = filePath.section("/",-1,-1);
    return fileName;
}

void tabchildwidget::on_textEdit_textChanged()
{
    updateLineNum();
    textChange();
    updateScroll(ui->textEdit->verticalScrollBar()->value());
    changed = true;
}

bool tabchildwidget::isChanged(){
    return changed;
}

void tabchildwidget::setChanged(bool changed){
    this->changed = changed;
}

void tabchildwidget::setFileType(){
    QRegularExpression scpPattern("^.*\.(scp)$");
    QRegularExpression jsnPattern("^.*\.(json)$");
    if(fileName!=""){
        if(scpPattern.match(fileName).hasMatch()){
            fileType = "scp";
        }else if(jsnPattern.match(fileName).hasMatch()) {
            fileType = "jsn";
        }
    }
}

QString tabchildwidget::getFileType(){
    setFileType();
    return fileType;
}

int tabchildwidget::getLineNum(){
    if(this->isEmpty()){
        return 1;
    }else {
        int blockcount = ui->textEdit->document()->blockCount();
        return blockcount;
    }
}

void tabchildwidget::updateLineNum(){
    //qDebug()<<getLineNum();
    ui->lineNumEdit->clear();
    for(int i=1; i<=getLineNum(); i++){
//        qDebug()<<i;
        ui->lineNumEdit->append(QString::number(i));
    }
    int pos = ui->textEdit->verticalScrollBar()->value();
}

//update line number area scrollbar position
void tabchildwidget::updateScroll(int pos){
    ui->lineNumEdit->verticalScrollBar()->setValue(pos);
}

void tabchildwidget::on_textEdit_cursorPositionChanged()
{
    //qt code editor example: https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!ui->textEdit->isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(225,225,225);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    ui->textEdit->setExtraSelections(extraSelections);
}
