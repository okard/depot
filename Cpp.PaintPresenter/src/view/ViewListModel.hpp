#ifndef VIEWLISTMODEL_HPP
#define VIEWLISTMODEL_HPP

#include <QAbstractListModel>

#include "View.hpp"

class ViewListModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(int count READ count NOTIFY onChangedCount())

private:
	QList<View*> views_;

public:
	explicit ViewListModel(QObject *parent = 0);

	int count() const;

	Q_INVOKABLE View* get(int index);

signals:
	void onChangedCount();

public slots:
	void append(View*);

	// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	//Insert/remove rows

};

#endif // VIEWLISTMODEL_HPP
