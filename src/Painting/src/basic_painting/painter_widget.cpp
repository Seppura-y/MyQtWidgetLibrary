#include "painter_widget.h"

#include <QPainter>
#include <QPainterPath>

PainterWidget::PainterWidget(QWidget* p)
{
	this->setMinimumSize(800, 600);

	draw_type_ = DRAW_TYPE::polygon;
}

void PainterWidget::paintEvent(QPaintEvent* event)
{
	width_ = this->width();
	height_ = this->height();

	switch (draw_type_)
	{
	case DRAW_TYPE::point:
		drawPoint();
		break;

	case DRAW_TYPE::multipoints:
		drawMultipoints();
		break;

	case DRAW_TYPE::line:
		drawLine();
		break;

	case DRAW_TYPE::arc:
		drawArc();
		break;

	case DRAW_TYPE::rect:
		drawRect();
		break;

	case DRAW_TYPE::roundrect:
		drawRoundrect();
		break;

	case DRAW_TYPE::chord:
		drawChord();
		break;

	case DRAW_TYPE::ellipse:
		drawEllipse();
		break;

	case DRAW_TYPE::polygon:
		drawPolygon();
		break;

	case DRAW_TYPE::polyline:
		drawPolyline();
		break;

	case DRAW_TYPE::ConvexPloygon:
		drawConvexPloygon();
		break;

	case DRAW_TYPE::lines:
		drawLines();
		break;

	case DRAW_TYPE::path:
		drawPath();
		break;

	case DRAW_TYPE::pie:
		drawPie();
		break;

	case DRAW_TYPE::image:
		drawImage();
		break;

	case DRAW_TYPE::pixmap:
		drawPixmap();
		break;

	case DRAW_TYPE::draw_text:
		drawText();
		break;

	case DRAW_TYPE::draw_erase:
		drawErase();
		break;

	case DRAW_TYPE::draw_fillpath:
		drawFillpath();
		break;

	case DRAW_TYPE::draw_fillrect:
		drawFillrect();
		break;

	default:
		break;
	}
}

void PainterWidget::drawPoint()
{
	QPainter painter(this);
	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::red);
	pen.setStyle(Qt::SolidLine);
	painter.setPen(pen);
	painter.drawPoint(QPoint(width_ / 2, height_ / 2));
}

void PainterWidget::drawMultipoints()
{
	QPainter painter(this);
	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::blue);
	pen.setStyle(Qt::SolidLine);
	painter.setPen(pen);

	QPoint points[] = {
	QPoint(5 * width_ / 12,height_ / 4),
	QPoint(3 * width_ / 4, 5 * height_ / 12),
	QPoint(2 * width_ / 4, 5 * height_ / 12) };
	painter.drawPoints(points, 3);
}

void PainterWidget::drawLine()
{
	QPainter painter(this);

	//QLine Line(W / 4, H / 4, W / 2, H / 2);
	QLine Line(width_ / 4, height_ / 4, width_ / 2, height_ / 4);
	painter.drawLine(Line);
}

void PainterWidget::drawArc()
{
	QPainter painter(this);
	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	int startAngle = 90 * 16;
	int spanAngle = 90 * 16;
	painter.drawArc(rect, startAngle, spanAngle);
}

void PainterWidget::drawRect()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	painter.drawRect(rect);
}

void PainterWidget::drawRoundrect()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	painter.drawRoundedRect(rect, 20, 20);
}

void PainterWidget::drawChord()
{
	QPainter painter(this);
	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	int startAngle = 90 * 16;
	int spanAngle = 90 * 16;
	painter.drawChord(rect, startAngle, spanAngle);
}

void PainterWidget::drawEllipse()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	painter.drawEllipse(rect);
}

void PainterWidget::drawPolygon()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::red);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::SquareCap);
	pen.setJoinStyle(Qt::MiterJoin);
	painter.setPen(pen);

	QBrush brush;
	brush.setColor(Qt::yellow);
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);

	QPoint points[] = {
	QPoint(5 * width_ / 12,height_ / 4),
	QPoint(3 * width_ / 4,5 * height_ / 12),
	QPoint(5 * width_ / 12,3 * height_ / 4),
	QPoint(2 * width_ / 4,5 * height_ / 12) };
	painter.drawPolygon(points, 4);
}

void PainterWidget::drawPolyline()
{
	QPainter painter(this);

	QPoint points[] = {
	QPoint(5 * width_ / 12, height_ / 4),
	QPoint(3 * width_ / 4, 5 * height_ / 12),
	QPoint(5 * width_ / 12, 3 * height_ / 4),
	QPoint(2 * width_ / 4, 5 * height_ / 12) };
	painter.drawPolyline(points, 4);
}

void PainterWidget::drawConvexPloygon()
{
	QPainter painter(this);

	QPoint points[4] = {
		QPoint(5 * width_ / 12, height_ / 4),
		QPoint(3 * width_ / 4, 5 * height_ / 12),
		QPoint(5 * width_ / 12, 3 * height_ / 4),
		QPoint(width_ / 4, 5 * height_ / 12) };

	painter.drawConvexPolygon(points, 4);
}

void PainterWidget::drawLines()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	QVector<QLine> Lines;
	Lines.append(QLine(rect.topLeft(), rect.bottomRight()));
	Lines.append(QLine(rect.topRight(), rect.bottomLeft()));
	Lines.append(QLine(rect.topLeft(), rect.bottomLeft()));
	Lines.append(QLine(rect.topRight(), rect.bottomRight()));
	painter.drawLines(Lines);
}

void PainterWidget::drawPath()
{
	QPainter painter(this);
	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	QPainterPath path;
	path.addEllipse(rect);
	path.addRect(rect);
	painter.drawPath(path);
}

void PainterWidget::drawPie()
{
	QPainter painter(this);
	QRect    rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	int startAngle = 40 * 16;
	int spanAngle = 120 * 16;
	painter.drawPie(rect, startAngle, spanAngle);
}

void PainterWidget::drawImage()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	QImage image(":/res/res/icons/cat2.jpg");
	painter.drawImage(rect, image);
}

void PainterWidget::drawPixmap()
{
	QPainter painter(this);

	QRect    rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	QPixmap    pixmap(":/res/res/icons/cat2.jpg");
	painter.drawPixmap(rect, pixmap);
}

void PainterWidget::drawText()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	QFont font;
	font.setPointSize(30);
	font.setBold(true);
	painter.setFont(font);
	painter.drawText(rect, "Hello,Qt");
}

void PainterWidget::drawErase()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	painter.eraseRect(rect);
}

void PainterWidget::drawFillpath()
{
	QPainter painter(this);

	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	QPainterPath path;
	path.addEllipse(rect);
	path.addRect(rect);
	painter.fillPath(path, Qt::red);
}

void PainterWidget::drawFillrect()
{
	QPainter painter(this);
	QRect rect(width_ / 4, height_ / 4, width_ / 2, height_ / 2);
	painter.fillRect(rect, Qt::green);
}

void PainterWidget::setDrawType(DRAW_TYPE type)
{
	draw_type_ = type;
}
