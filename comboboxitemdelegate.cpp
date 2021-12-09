#include <comboboxitemdelegate.h>
#include <QComboBox>
#include <QSqlQuery>

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent, const QString &visualColumn, const QString &queryTail)
    :QStyledItemDelegate(parent)
{
    this->visualColumn = visualColumn;
    this->queryTail = queryTail;
}

//~ComboBoxItemDelegate() = default;
//
QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    auto *editor = new QComboBox(parent);
    QSqlQuery query;
    query.prepare( QString( "SELECT %1.id, %2 FROM %3" ).arg( queryTail.split( ' ' ).first() ).arg( visualColumn ).arg( queryTail ) );
    query.exec();

    while (query.next()) {
        editor->addItem(query.value(1).toString(), query.value(0));
    }
    return editor;
}
//Постобработка выбранного элемента в ComboBox
void ComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto *comboBox = dynamic_cast<QComboBox*>(editor);
    QString currentText = index.data(Qt::EditRole).toString();
    int cbIndex = comboBox->findText(currentText);
    if (cbIndex >= 0)
        comboBox->setCurrentIndex(cbIndex);
}
//Вызывается для просмотра, устанавливает значение в ячейке
void ComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (auto *comboBox = dynamic_cast<QComboBox*>(editor)) {
        QVariant modelData = comboBox->itemData(comboBox->currentIndex(), Qt::UserRole);    // id из Qt::UserRole
        model->setData(index, modelData.toString(), Qt::EditRole);
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void ComboBoxItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
