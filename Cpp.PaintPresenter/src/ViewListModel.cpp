#include "ViewListModel.hpp"

ViewListModel::ViewListModel(QObject *parent) :
	QAbstractListModel(parent)
{
}

int ViewListModel::count() const
{
	return views_.count();
}

View* ViewListModel::get(int index)
{
	if(index < 0 || index >= views_.count())
		return nullptr;

	return views_[index];
}

void ViewListModel::append(View* v)
{
	if(v == nullptr)
		return;

	beginInsertRows(QModelIndex(), count(), count());
	views_.append(v);
	endInsertRows();

	emit dataChanged(createIndex(0,0), createIndex(count()-1, 0));
	emit onChangedCount();
}

int ViewListModel::rowCount(const QModelIndex& parent) const
{
	return views_.count();
}

QVariant ViewListModel::data(const QModelIndex& index, int role) const
{
	if(!index.isValid())
			return QVariant();

	if (index.row() >= views_.size())
		  return QVariant();

	if(role == Qt::DisplayRole)
	{
		return views_.at(index.row())->name();
	}

	//todo find modelData role out here

	return QVariant();
}

QVariant ViewListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
			return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return ("View");

		default:
			return QVariant();
		}
	}
	else
	{
		return QString("View %1").arg(section);
	}
}
