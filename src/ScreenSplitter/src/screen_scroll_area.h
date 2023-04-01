#ifndef SCREEN_SCROLL_AREA_H
#define SCREEN_SCROLL_AREA_H
#include <QScrollArea>
#include <QMenu>
#include <QContextMenuEvent>
class ScreenScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	ScreenScrollArea(QWidget* parent = nullptr);

	void contextMenuEvent(QContextMenuEvent* ev) override;

	void set_merge_enable(bool en = true);
	void set_split_enable(bool en = true);
	int get_horizontal_scrollbar_height();
signals:
	void merge();
	void split();
	void clear();
	void save();
	void load();
	void rstsvr();
	void sndfile();
	void setaddr();

public slots:
	void emit_merge();
	void emit_split();
	void emit_clear();
	void emit_save();
	void emit_load();
	void emit_rstsvr();
	void emit_sndfile();
	void emit_setaddr();
private:
	QMenu menu_;
};

#endif