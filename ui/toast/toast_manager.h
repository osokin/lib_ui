// This file is part of Desktop App Toolkit,
// a set of libraries for developing nice desktop applications.
//
// For license and copyright information please follow this link:
// https://github.com/desktop-app/legal/blob/master/LEGAL
//
#pragma once

#include "ui/toast/toast.h"
#include "base/timer.h"

namespace Ui {
namespace Toast {
namespace internal {

class Widget;
class Manager : public QObject {
	Q_OBJECT

	struct CreateTag {
	};

public:
	Manager(not_null<QWidget*> parent, const CreateTag &);
	Manager(const Manager &other) = delete;
	Manager &operator=(const Manager &other) = delete;
	~Manager();

	static not_null<Manager*> instance(not_null<QWidget*> parent);

	void addToast(std::unique_ptr<Instance> &&toast);

protected:
	bool eventFilter(QObject *o, QEvent *e);

private slots:
	void onToastWidgetDestroyed(QObject *widget);

private:
	void startNextHideTimer();
	void hideByTimer();

	base::Timer _hideTimer;
	crl::time _nextHide = 0;

	QMultiMap<crl::time, Instance*> _toastByHideTime;
	QMap<Widget*, Instance*> _toastByWidget;
	QList<Instance*> _toasts;
	OrderedSet<QPointer<QWidget>> _toastParents;

};

} // namespace internal
} // namespace Toast
} // namespace Ui
