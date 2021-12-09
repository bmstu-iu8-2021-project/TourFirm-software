#include "dateeditdelegate.h"
#include <QDateEdit>
#include <QStyleOptionViewItemV2>

DateEditDelegate::DateEditDelegate(QObject *parent)
    :QItemDelegate(parent){}

QWidget *DateEditDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/*option*/,
    const QModelIndex &/*index*/) const
{

    QDateEdit *date = new QDateEdit(parent);
    date->setFrame(false);
    date->setMinimumDate(QDate(2015, 12, 01));
    date->setMaximumDate(QDate(2099, 12, 01));
    date->setDate(QDate::currentDate());
    date->setCalendarPopup(true);
    date->setDisplayFormat("yyyy/MM/dd");
    return date;
}

void DateEditDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QDate value = index.model()->data(index, Qt::EditRole).toDate();
    QDateEdit *date = static_cast<QDateEdit*>(editor);
    date->setDate(value);
}

void DateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QDateEdit *date = static_cast<QDateEdit*>(editor);
    date->interpretText();
    model->setData(index, date->date(), Qt::EditRole);
}

void DateEditDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}

void DateEditDelegate::paint(QPainter *painter,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    QStyleOptionViewItemV2 opt = setOptions(index, option);
    opt.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    drawDisplay(painter, opt, opt.rect, index.data(Qt::DisplayRole).toDate().toString("yyyy/MM/dd"));
}
