#include "item_select_widget.h"

#include "draw_type.h"

#include <QStandardItemModel>
#include <QHBoxLayout>


ItemSelectWidget::ItemSelectWidget(QWidget* parent)
	: QWidget(parent)
{
    setWindowTitle(u8"draw all");

    QHBoxLayout* h_layout = new QHBoxLayout(this);
    item_tree_ = new QTreeView(this);
    item_tree_->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    item_tree_->setFixedWidth(300);

    painter_widget_ = new PainterWidget(this);
    h_layout->addWidget(item_tree_);
    h_layout->addWidget(painter_widget_);

    treeView();
}

ItemSelectWidget::~ItemSelectWidget()
{

}

void ItemSelectWidget::treeView()
{
    item_tree_->setFrameShape(QFrame::NoFrame);

    QStandardItemModel* model = new QStandardItemModel(item_tree_);
    model->setHorizontalHeaderLabels(QStringList() << "draw all");

    QStandardItem* parent_item = NULL;
    QStandardItem* child_item = NULL;

    // 点
    parent_item = new QStandardItem(QIcon(":/res/icons/point.png"), "draw ponit");
    model->appendRow(parent_item);

    child_item = new QStandardItem(QIcon(":/res/icons/point.png"), "point");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/multipoints.png"), "multipoints");
    parent_item->appendRow(child_item);

    // 线
    parent_item = new QStandardItem(QIcon(":/res/icons/line.png"), "draw line");
    model->appendRow(parent_item);

    child_item = new QStandardItem(QIcon(":/res/icons/line.png"), "line");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/arc.png"), "arc");
    parent_item->appendRow(child_item);

    // 封闭的图形
    parent_item = new QStandardItem(QIcon(":/res/icons/rect.png"), "draw rect");
    model->appendRow(parent_item);

    child_item = new QStandardItem(QIcon(":/res/icons/rect.png"), "rect");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/roundrect.png"), "roundrect");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/chord.png"), "chord");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/ellipse.png"), "ellipse");
    parent_item->appendRow(child_item);

    // 任意路径绘制
    parent_item = new QStandardItem(QIcon(":/res/icons/polygon.png"), "draw polygon");
    model->appendRow(parent_item);

    child_item = new QStandardItem(QIcon(":/res/icons/polygon.png"), "polygon");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/polyline.png"), "polyline");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/ConvexPloygon.png"), "ConvexPloygon");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/lines.png"), "lines");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/path.png"), "path");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/pie.png"), "pie");
    parent_item->appendRow(child_item);

    // 图片绘制
    parent_item = new QStandardItem(QIcon(":/res/icons/image.png"), "draw image");
    model->appendRow(parent_item);

    child_item = new QStandardItem(QIcon(":/res/icons/image.png"), "image");
    parent_item->appendRow(child_item);

    child_item = new QStandardItem(QIcon(":/res/icons/pixmap.png"), "pixmap");
    parent_item->appendRow(child_item);

    // 文本绘制
    parent_item = new QStandardItem(QIcon(":/res/icons/text.png"), "draw text");
    model->appendRow(parent_item);

    // 擦除
    parent_item = new QStandardItem(QIcon(":/res/icons/erase.png"), "draw erase");
    model->appendRow(parent_item);

    // 路径填充
    parent_item = new QStandardItem(QIcon(":/res/icons/fillpath.png"), "draw fillpath");
    model->appendRow(parent_item);

    // 矩形填充
    parent_item = new QStandardItem(QIcon(":/res/icons/fillrect.png"), "draw fillrect");
    model->appendRow(parent_item);

    item_tree_->setModel(model);

    connect(item_tree_, &QAbstractItemView::clicked, this, &ItemSelectWidget::onTreeViewExpand);
}

void ItemSelectWidget::onTreeViewExpand(const QModelIndex& index)
{
    QString text = index.data().toString();

    if (text.compare("point") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::point);
        painter_widget_->update();  //不更新就不会立即显示
    }
    else if (text.compare("multipoints") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::multipoints);
        painter_widget_->update();
    }
    else if (text.compare("line") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::line);
        painter_widget_->update();
    }
    else if (text.compare("arc") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::arc);
        painter_widget_->update();
    }
    else if (text.compare("rect") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::rect);
        painter_widget_->update();
    }
    else if (text.compare("roundrect") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::roundrect);
        painter_widget_->update();
    }
    else if (text.compare("chord") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::chord);
        painter_widget_->update();
    }
    else if (text.compare("ellipse") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::ellipse);
        painter_widget_->update();
    }
    else if (text.compare("polygon") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::polygon);
        painter_widget_->update();
    }
    else if (text.compare("polyline") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::polyline);
        painter_widget_->update();
    }
    else if (text.compare("ConvexPloygon") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::ConvexPloygon);
        painter_widget_->update();
    }
    else if (text.compare("lines") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::lines);
        painter_widget_->update();
    }
    else if (text.compare("path") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::path);
        painter_widget_->update();
    }
    else if (text.compare("pie") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::pie);
        painter_widget_->update();
    }
    else if (text.compare("image") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::image);
        painter_widget_->update();
    }
    else if (text.compare("pixmap") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::pixmap);
        painter_widget_->update();
    }
    else if (text.compare("draw text") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::draw_text);
        painter_widget_->update();
    }
    else if (text.compare("draw erase") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::draw_erase);
        painter_widget_->update();
    }
    else if (text.compare("draw fillpath") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::draw_fillpath);
        painter_widget_->update();
    }
    else if (text.compare("draw fillrect") == 0)
    {
        painter_widget_->setDrawType(DRAW_TYPE::draw_fillrect);
        painter_widget_->update();
    }
}